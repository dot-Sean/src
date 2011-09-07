import optparse

optpsr = optparse.OptionParser(usage = "usage: hoge fuga ...")
optpsr.add_option("-a", "--alpha", dest = "alpha", action = "store",
 type = "string", default = defconfig

(opts, args,) = optpsr.parse_args()
