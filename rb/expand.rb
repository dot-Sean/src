#!/usr/bin/ruby

# Error
# print("#{'}'}")

print("Expression list: #{begin '{'; '}' end}\n")

print("Quoted: #{\"\x7D\"}\n")

print("Regex: #{/\x7D/}\n")

print("Format: #{'%c' % [0x7D]}\n")


