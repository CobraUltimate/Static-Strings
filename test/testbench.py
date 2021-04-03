import serial
from colorama import init
from termcolor import colored

# use Colorama to make Termcolor work on Windows too
init()

ser = serial.Serial()
ser.port = 'COM8'
ser.baudrate = 115200
ser.open()

#very large string allocate and deallocate test

#test 1

very_large_string_length = ser.readline()
print(very_large_string_length )
if very_large_string_length == b'0699\r\n':
	print(colored('success test 1.1','blue'))
else:
	print(colored('fail test 1.1','red'))
very_large_string_type = ser.readline()
print(very_large_string_type )
if very_large_string_type == b'4\r\n':
	print(colored('success test 1.2','blue'))
else:
	print(colored('fail test 1.2','red'))
very_large_string = ser.read(699)
print(very_large_string )
if very_large_string == b'aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa':
	print(colored('success test 1.3','blue'))
else:
	print(colored('fail test 1.3','red'))

#very large string reallocation test

string_length = ser.readline()
print(string_length )
if string_length == b'0602\r\n':
	print(colored('success test 2.1','blue'))
else:
	print(colored('fail test 2.1','red'))
string_type = ser.readline()
print(string_type )
if string_type == b'4\r\n':
	print(colored('success test 2.2','blue'))
else:
	print(colored('fail test 2.2','red'))
string = ser.readline()
print(string )
if string == b'3ghgwfrwyrzzdhr2929pnvm7ht4bgvq6bii7cz7ajp98475pgbwt3tww7prn86y7e6gdhvda923y4wzu5xwex9a8ntjf243h94z848k9fhym39qrt8ypp9rcge8drmxfeb9bn5mryc738w2mdk8weyxnti2zy9a7j3w7947qhce3bvv5d8yjxxt7ncik4muju5zcqzab5vf2wvz49w3j8v23u3grci33hdxvniy7h2p2r4b4xig3j5nfnn6m2qvmw5b5hzii32mrh7ebr2tuaqgdxn8xbecjpnvpv7timpd7cpqyubdjczaftwrrum8bdtfqzp4wr8him9n3g4nc347f264jhzb7w6bmyh9gj3zwrau6czz67ybq2cdh6p7cdbyvk88u5rfh9xi3u6fgbzfnu9b9qv6kd4mxhc6t758tad8n4i396qw2v3r2th3dag8d7h837ibpdx8v8njvkg7dh9j5rqmnvktcegmtxaprhxky8f6ppwcgeei29a6z3inht7kzm9x62muqc6cijrzfqm3yvukurwge4mi5fnzb5gqbz279kbpzy484ndrc2vrczwa2zmvjvdad39vjtwqp\r\n':
	print(colored('success test 2.3','blue'))
else:
	print(colored('fail test 2.2','red'))

#large string allocation test

string_length = ser.readline()
print(string_length )
if string_length == b'0352\r\n':
	print(colored('success test 3.1','blue'))
else:
	print(colored('fail test 3.1','red'))
string_type = ser.readline()
print(string_type )
if string_type == b'3\r\n':
	print(colored('success test 3.2','blue'))
else:
	print(colored('fail test 3.2','red'))
string = ser.readline()
print(string )
if string == b'2j97e72cutbnqwcc4rg6rvqniyravzyqj4k7ee44pwvwmi2kvdk3vmmbr7396q7uajqmukehfn7qhr9pj4k974wbiw6dxr9ckmmj4bnkd5ndxn6ia27rjyyhdnrgk2kgdrqfhkeq8jwdz9rgd6wyw52yqxz5v873j7q9gc3bwfmiv6deutkj7fvvg8m877tgtnq5a5ueqd589prwfk5ex7bjixicnhb3x9n9m5vqtpbtgzx4vvbc9jcqrpfbgxjpvawrkeyjkk7aifkfr6xjerkxz7bk6cekpqttf72788m23qaz7xncba4g8dvayzwqqyev6ie3dgyfyew2rew6nba9nte3p5\r\n':
	print(colored('success test 3.3','blue'))
else:
	print(colored('fail test 3.3','red'))

#medium string allocation test

medium_test_strings_lengths = [b'0152\r\n',b'0122\r\n']
medium_test_strings = [b'27wnc489rtjak6963r7c8mw4zmm7nxkhneu9wbg6nemurramx4yx6zipi2kmjh3n9hr6aci9dcku5w87ez8fkr5fnuzdk8q74ekkwgfnm3kq7dk82d24vujdpupp83rbfw5bnci7h5zx6iuzadukvc\r\n',b'ieckbpek2tuq837haz8cy78dpki9eav589t2bx5ffkx44kcj9tw5hwqyfqwgi5mjrww2i39jg9hz7djdddyp3b6uyy69cniwzeu8y4kgv2xmkji97dpxcfhr\r\n']

for i in range(2):
	
	string_length = ser.readline()
	print(string_length )
	if string_length == medium_test_strings_lengths[i]:
		print(colored('success test 4-5.1','blue'))
	else:
		print(colored('fail test 4-5.1','red'))
	string_type = ser.readline()
	print(string_type)
	if string_type == b'2\r\n':
		print(colored('success test 4-5.2','blue'))
	else:
		print(colored('fail test 4-5.2','red'))
	string = ser.readline()
	print(string )
	if string == medium_test_strings[i]:
		print(colored('success test 4-5.3','blue'))
	else:
		print(colored('fail test 4-5.3','red'))

#short string allocation test

short_test_strings_lengths = [b'0062\r\n',b'0067\r\n',b'0072\r\n',b'0077\r\n',b'0082\r\n',b'0087\r\n']
short_test_strings = [b'b6cwufw3yyfz4kdxmpmjbt8p5kq43m8hynkanabtjrgrc4iitx8tvdbkgima\r\n',b'j85npdf3rjtf8egmja2cxuqgu6z4h38ikaue7evfqytbuw5b95pjmqvnhejmjkc8c\r\n',b'bduzvngtikgxbm2wc4wrwq75ti4c5cvavcna7k4cur4mi56gegbfnc5jd6i484efri9ddh\r\n',b'44upv7qtmzngmbp7gdbfnumhx82iwpz8vtp9dd7vyq4yn56jqfj7g5pd44gxg9t5tw466u6gbum\r\n',b'5gpxtjyj79j438uif2ukmyj67v5hebnh45tpaxa9cc92t28nwct2hghqb7kf96vrzz9dqj6hcfqtjfyi\r\n',b'e7gbz5rqwhmr3bq6jfuav9hgya8fthpi4jn6yiwgd5hmv9mjke8r8eva7dbzyr2pn9wavx386u6dnj6zdkerc\r\n']

for i in range(6):
	
	string_length = ser.readline()
	print(string_length )
	if string_length == short_test_strings_lengths[i]:
		print(colored('success test 6-11.1','blue'))
	else:
		print(colored('fail test 6-11.1','red'))
	string_type = ser.readline()
	print(string_type)
	if string_type == b'1\r\n':
		print(colored('success test 6-11.2','blue'))
	else:
		print(colored('fail test 6-11.2','red'))
	string = ser.readline()
	print(string )
	if string == short_test_strings[i]:
		print(colored('success test 6-11.3','blue'))
	else:
		print(colored('fail test 6-11.3','red'))

#very short string allocation test

very_short_test_strings_lengths = [b'0007\r\n',b'0012\r\n',b'0017\r\n',b'0022\r\n',b'0027\r\n',b'0032\r\n',b'0037\r\n',b'0042\r\n',b'0047\r\n',b'0050\r\n']
very_short_test_strings = [b'rapmr\r\n',b'ejkxjde7wp\r\n',b'rmp642c8un8bcjj\r\n',b'5ynn4y8caurm3trzwq4j\r\n',b'hwcqtzcn4gc8avg4d4zi7nr9f\r\n',b'tgt62yw9jnugwbg3pgzax73z6uix7g\r\n',b'bwn8czmxkhexdiw77v4gk4xu2yqtqibv2jn\r\n',b'eykku6i7j36kewjbwvpd5x9viggdhreqe9amk7ub\r\n',b'mpjkqkrn22q4xzvpt897fwjjurgtj3vczmmhy64d8qgww\r\n',b'wgxfec343aaku5axbjt5w2e5cz63r9bbydqun88ukj9iwint\r\n']

for i in range(10):
	
	string_length = ser.readline()
	print(string_length )
	if string_length == very_short_test_strings_lengths[i]:
		print(colored('success test 12-21.1','blue'))
	else:
		print(colored('fail test 12-21.1','red'))
	string_type = ser.readline()
	print(string_type)
	if string_type == b'0\r\n':
		print(colored('success test 12-21.2','blue'))
	else:
		print(colored('fail test 12-21.2','red'))
	string = ser.readline()
	print(string )
	if string == very_short_test_strings[i]:
		print(colored('success test 12-21.3','blue'))
	else:
		print(colored('fail test 12-21.3','red'))

string_length = ser.readline()
print(string_length)
if string_length == b'0017\r\n':
	print(colored('success test 22.1','blue'))
else:
	print(colored('fail test 22.1','red'))
string_type = ser.readline()
print(string_type)
if string_type == b'0\r\n':
	print(colored('success test 22.2','blue'))
else:
	print(colored('fail test 22.2','red'))
string = ser.readline()
print(string )
if string == b'reallocate_test\r\n':
	print(colored('success test 22.3','blue'))
else:
	print(colored('fail test 22.3','red'))

pointer_deallocate = print(ser.readline())
pointer_reallocate = print(ser.readline())
if pointer_deallocate == pointer_reallocate:
	print(colored('success test 23','blue'))
else:
	print(colored('fail test 23','red'))

error_code = ser.read()
print(error_code)
if error_code == b'1':
	print(colored('success test 24','blue'))
else:
	print(colored('fail test 24','red'))

error_code = ser.read()
print(error_code)
if error_code == b'3':
	print(colored('success test 25','blue'))
else:
	print(colored('fail test 25','red'))

error_code = ser.read()
print(colored('success test 26 - deprecated','blue'))

error_code = ser.read()
print(colored('success test 27 deprecated','blue'))

null_terminated = ser.read(9)
print(null_terminated)
if null_terminated == b'123,56,89':
	print(colored('success test 28','blue'))
else:
	print(colored('fail test 28','red'))

is_line = ser.readline()
print(is_line)
if is_line == b'0\r\n':
	print(colored('success test 29','blue'))
else:
	print(colored('fail test 29','red'))

is_line = ser.readline()
print(is_line)
if is_line == b'1\r\n':
	print(colored('success test 30','blue'))
else:
	print(colored('fail test 30','red'))

token = ser.read(3)
print(token)
if token == b'123':
	print(colored('success test 31','blue'))
else:
	print(colored('fail test 31','red'))

token = ser.read(2)
print(token)
if token == b'56':
	print(colored('success test 32','blue'))
else:
	print(colored('fail test 32','red'))

token = ser.readline()
print(token)
if token == b'8\r\n':
	print(colored('success test 33','blue'))
else:
	print(colored('fail test 33','red'))

next_token_result = ser.readline()
print(next_token_result)
if next_token_result == b'0\r\n':
	print(colored('success test 34','blue'))
else:
	print(colored('fail test 34','red'))

substring = ser.read(6)
print(substring)
if substring == b'3,56,8':
	print(colored('success test 35','blue'))
else:
	print(colored('fail test 35','red'))

substring = ser.read(9)
print(substring)
if substring == b'123,56,89':
	print(colored('success test 36','blue'))
else:
	print(colored('fail test 36','red'))

substring = ser.readline()
print(substring)
if substring == b'0\r\n':
	print(colored('success test 37','blue'))
else:
	print(colored('fail test 37','red'))

substring = ser.readline()
print(substring)
if substring == b'0\r\n':
	print(colored('success test 38','blue'))
else:
	print(colored('fail test 38','red'))

concatenated = ser.readline()
print(concatenated)
if concatenated == b'Hello World\r\n':
	print(colored('success test 39','blue'))
else:
	print(colored('fail test 39','red'))

contains = ser.readline()
print(contains)
if contains == b'1\r\n':
	print(colored('success test 40','blue'))
else:
	print(colored('fail test 40','red'))

contains = ser.readline()
print(contains)
if contains == b'1\r\n':
	print(colored('success test 41','blue'))
else:
	print(colored('fail test 41','red'))

contains = ser.readline()
print(contains)
if contains == b'0\r\n':
	print(colored('success test 42','blue'))
else:
	print(colored('fail test 42','red'))

contains = ser.readline()
print(contains)
if contains == b'1\r\n':
	print(colored('success test 43','blue'))
else:
	print(colored('fail test 43','red'))

contains = ser.readline()
print(contains)
if contains == b'1\r\n':
	print(colored('success test 44','blue'))
else:
	print(colored('fail test 44','red'))

contains = ser.readline()
print(contains)
if contains == b'0\r\n':
	print(colored('success test 45','blue'))
else:
	print(colored('fail test 45','red'))

equals = ser.readline()
print(equals)
if equals == b'1\r\n':
	print(colored('success test 46','blue'))
else:
	print(colored('fail test 46','red'))

equals = ser.readline()
print(equals)
if equals == b'0\r\n':
	print(colored('success test 47','blue'))
else:
	print(colored('fail test 47','red'))

number_string = ser.read(3)
print(number_string)
if number_string == b'200':
	print(colored('success test 48','blue'))
else:
	print(colored('fail test 48','red'))

number_string = ser.read(5)
print(number_string)
if number_string == b'64200':
	print(colored('success test 49','blue'))
else:
	print(colored('fail test 49','red'))

number_string = ser.read(10)
print(number_string)
if number_string == b'1000064200':
	print(colored('success test 50','blue'))
else:
	print(colored('fail test 50','red'))

number_string = ser.read(3)
print(number_string)
if number_string == b'100':
	print(colored('success test 51','blue'))
else:
	print(colored('fail test 51','red'))

number_string = ser.read(6)
print(number_string)
if number_string == b'-32100':
	print(colored('success test 52','blue'))
else:
	print(colored('fail test 52','red'))

number_string = ser.read(9)
print(number_string)
if number_string == b'500032100':
	print(colored('success test 53','blue'))
else:
	print(colored('fail test 53','red'))

number_string = ser.read(9)
print(number_string)
if number_string == b'19.602320':
	print(colored('success test 54','blue'))
else:
	print(colored('fail test 54','red'))

number_string = ser.read(12)
print(number_string)
if number_string == b'-1924.234200':
	print(colored('success test 55','blue'))
else:
	print(colored('fail test 55','red'))

copy_string = ser.readline()
print(copy_string)
if copy_string == b'I am a copy test\r\n':
	print(colored('success test 56','blue'))
else:
	print(colored('fail test 56','red'))
	print(ser.read())

clone_string = ser.readline()
print(clone_string)
if clone_string == b'I am a clone test\r\n':
	print(colored('success test 57','blue'))
else:
	print(colored('fail test 57','red'))
	print(ser.read())

move_string = ser.readline()
print(move_string)
if move_string == b'.I am a move test\r\n':
	print(colored('success test 58','blue'))
else:
	print(colored('fail test 58','red'))
	print(ser.read())

concatenate_string = ser.readline()
print(concatenate_string)
if concatenate_string == b'I am a concatenate test\r\n':
	print(colored('success test 59','blue'))
else:
	print(colored('fail test 59','red'))
	print(ser.read())

concatenate_string = ser.readline()
print(concatenate_string)
if concatenate_string == b'I am a concatenate all test\r\n':
	print(colored('success test 60','blue'))
else:
	print(colored('fail test 60','red'))
	print(ser.read())

concatenate_and_clean_both_string = ser.readline()
print(concatenate_and_clean_both_string)
if concatenate_and_clean_both_string == b'I am a concatenate test\r\n':
	print(colored('success test 61','blue'))
else:
	print(colored('fail test 61','red'))
	print(ser.read())

concatenate_and_clean__all__string = ser.readline()
print(concatenate_and_clean__all__string)
if concatenate_and_clean__all__string == b'I am a concatenate all test\r\n':
	print(colored('success test 62','blue'))
else:
	print(colored('fail test 62','red'))
	print(ser.read())

new_line = ser.readline()
print(new_line)
if new_line == b'\r\n':
	print(colored('success test 63','blue'))
else:
	print(colored('fail test 63','red'))

empty_line_test_result = ser.readline()
print(empty_line_test_result)
if empty_line_test_result == b'success\r\n':
	print(colored('success test 64','blue'))
else:
	print(colored('fail test 64','red'))
