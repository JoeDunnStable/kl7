test_kl7 = executable('test-kl7', 
                       ['test-kl7.cpp',
			'../kl7-cli/kl7.cpp',
			'../kl7-cli/dr_wiring.cpp'],
                        dependencies : boostdep,
			include_directories: incdir) 

my_timeout = 100

test('test_kl7', test_kl7 ,timeout: my_timeout)


