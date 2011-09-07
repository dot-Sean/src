#!/usr/bin/python

import sys
import logging

verbose=1

logging.basicConfig(level = logging.DEBUG)
logging.debug('A debug message')

logger = logging.getLogger("foo.normal")
# put the logs >= ERROR
logger.setLevel(logging.ERROR)
logger_verbose = logging.getLogger("foo.verbose")
# put the logs >= DEBUG
logging.getLogger("foo.verbose").setLevel(logging.DEBUG)

stdout_stream = logging.StreamHandler(sys.stdout)
stdout_stream.setFormatter(logging.Formatter("*** name: %(name)s, levelname: %(levelname)s, asctime: %(asctime)s,  %(message)s"))
logger_verbose.addHandler(stdout_stream)

print logger_verbose.handlers
#logger_verbose.propagate = False

logger.info("info normal")
logger.warning("warning normal")
logger.error("error normal")

logger_verbose.info("info verbose")
logger_verbose.warning("warning verbose")
logger_verbose.error("error verbose")

logger_all = logging.getLogger("foo.verbose.cli.debug")
logger_all.error("error debug")
