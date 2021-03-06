#!/usr/bin/env python

from hhAnalysis.multilepton.configs.denomHistogramConfig import denomHistogramConfig, validate_denom
from hhAnalysis.multilepton.common import is_nonresonant
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no
from tthAnalysis.HiggsToTauTau.runConfig import tthAnalyzeParser, filter_samples
from tthAnalysis.HiggsToTauTau.common import logging, load_samples

import os
import sys
import getpass
import re

# E.g.: ./test/hhNonResDenom.py -v 2019May09 -e 2017 -m bbww

mode_choices = [ 'hh_multilepton', 'hh_bbww', 'hh_bbww_sync' ]

parser = tthAnalyzeParser(default_num_parallel_jobs = 40)
parser.add_modes(mode_choices)
parser.add_files_per_job(100)
parser.add_use_home()
parser.add_argument('-P', '--use-preprocessed',
  dest = 'use_preprocessed', action = 'store_true', default = False,
  help = 'R|Use Ntuples that have not been post-processed yet',
)
parser.add_argument('-V', '--validate',
  dest = 'validate', action = 'store_true', default = False,
  help = 'R|Validate the results',
)
parser.add_argument('-o', '--output-file',
  type = str, dest = 'output_file', metavar = 'filename', default = 'denom_{era}.root',
  required = False,
  help = 'R|File name of the output file',
)
args = parser.parse_args()

# Common arguments
era                = args.era
version            = args.version
dry_run            = args.dry_run
no_exec            = args.no_exec
auto_exec          = args.auto_exec
check_output_files = not args.not_check_input_files
sample_filter      = args.filter
num_parallel_jobs  = args.num_parallel_jobs
running_method     = args.running_method

# Additional arguments
mode          = args.mode
files_per_job = args.files_per_job
validate      = args.validate
use_home      = args.use_home
use_preproc   = args.use_preprocessed

# Custom arguments
output_file = args.output_file

# Use the arguments
if '{era}' in output_file:
  output_file = output_file.format(era = era)

if mode == 'hh_multilepton':
  samples = load_samples(era, not use_preproc, base = 'hh_multilepton')
elif mode == 'hh_bbww':
  samples = load_samples(era, not use_preproc, base = 'hh_bbww')
elif mode == 'hh_bbww_sync':
  samples = load_samples(era, not use_preproc, base = 'hh_bbww', suffix = 'sync')
else:
  raise ValueError('Invalid mode: %s' % mode)

if mode != 'hh_bbww_sync':
  for sample_name, sample_entry in samples.items():
    if sample_name == 'sum_events': continue
    sample_entry['use_it'] = is_nonresonant(sample_entry['sample_category'])

if __name__ == '__main__':
  if sample_filter:
    samples = filter_samples(samples, sample_filter)
  if 'sum_events' in samples:
    del samples['sum_events']

  configDir = os.path.join("/home",       getpass.getuser(), "hhDenomProduction", era, version)
  outputDir = os.path.join("/hdfs/local", getpass.getuser(), "hhDenomProduction", era, version)

  if validate:
    validation_result = validate_denom(os.path.join(outputDir, output_file), samples)
    sys.exit(validation_result)

  denomHistogramProduction = denomHistogramConfig(
    configDir          = configDir,
    outputDir          = outputDir,
    output_file        = output_file,
    executable         = "denomHistogramProducer.sh",
    samples            = samples,
    max_files_per_job  = files_per_job,
    era                = era,
    check_output_files = check_output_files,
    running_method     = running_method,
    num_parallel_jobs  = num_parallel_jobs,
    dry_run            = dry_run,
    use_home           = use_home,
    submission_cmd     = sys.argv,
  )

  job_statistics = denomHistogramProduction.create()
  for job_type, num_jobs in job_statistics.items():
    logging.info(" #jobs of type '%s' = %i" % (job_type, num_jobs))

  if auto_exec:
    run_denomHistogramProduction = True
  elif no_exec:
    run_denomHistogramProduction = False
  else:
    run_denomHistogramProduction = query_yes_no("Start jobs ?")
  if run_denomHistogramProduction:
    denomHistogramProduction.run()
  else:
    sys.exit(0)
