import cce
h = cce.cce_handle_new()
cce.cce_connect_cmnd(h, "/usr/sausalito/cced.socket")
p = cce.cce_props_new()
a = cce.cce_find_cmnd(h, "Network", p)
print a
print cce.cce_get_cmnd(h, a[0], "")
a = cce.cce_find_cmnd(h, "Inittab", p)
print a
print cce.cce_get_cmnd(h, a[0], "")
