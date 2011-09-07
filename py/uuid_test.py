#!/usr/bin/python

import uuid

uuid1 = uuid.uuid1()
# in ascii string
print(str(uuid1))
# in byte string
print(uuid1.bytes)
# creates UUID from a byte string
print(uuid.UUID(bytes = uuid1.bytes))
