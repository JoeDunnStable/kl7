kl7 = executable('kl7', 
                       [ 'main.cpp', 'kl7.cpp', 'dr_wiring.cpp'],
                        dependencies : boostdep) 


my_timeout = 10

test('kl7-help', kl7, args : '--help' , timeout: my_timeout)
test('kl7-e', kl7, args : '-e', should_fail : true, timeout: my_timeout)
test('kl7-d', kl7, args : '-d', should_fail : true, timeout: my_timeout)
test('kl7-ei', kl7, args :['-e', '--text', 'HELLO WORLD'], timeout: my_timeout)
test('kl7-di', kl7, args :['-d', '--text', 'DPONI NEHEU K'], timeout: my_timeout)
test('kl7-edi', kl7, args :['-d', '-e', '--text', 'DPONI NEHEU K'],
     should_fail: true, timeout: my_timeout)
test('kl7-ei-rC', kl7,
     args: ['-e', '--text', 'HELLO WORLD', '--rotorCore', 'MLKJIHGF'],
     timeout: my_timeout)
test('kl7-ei-rC7', kl7,
     args: ['-e', '--text', 'HELLO WORLD', '--rotorCore', 'MLKJIHG'],
     should_fail : true, timeout: my_timeout)
test('kl7-ei-rC9', kl7,
     args: ['-e', '--text', 'HELLO WORLD', '--rotorCore', 'MLKJIHGFE'],
     should_fail : true, timeout: my_timeout)
test('kl7-ei-rC-N', kl7,
     args: ['-e', '--text', 'HELLO WORLD', '--rotorCore', 'NLKJIHGF'],
     should_fail : true, timeout: my_timeout)
test('kl7-ei-rC-MM', kl7,
     args: ['-e', '--text', 'HELLO WORLD', '--rotorCore', 'MLKJIHGM'],
     should_fail : true, timeout: my_timeout)
test('kl7-ei-aRS', kl7,
     args: ['-e', '--text', 'HELLO WORLD', '--alphaRingSet', '1 2 3 4 5 6 7 8'],
     timeout: my_timeout)
test('kl7-ei-aRS7', kl7,
     args: ['-e', '--text', 'HELLO WORLD', '--alphaRingSet', '1 2 3 4 5 6 7'],
     should_fail: true, timeout: my_timeout)
test('kl7-ei-aRS9', kl7,
     args: ['-e', '--text', 'HELLO WORLD', '--alphaRingSet', '1 2 3 4 5 6 7 8 9'],
     should_fail: true, timeout: my_timeout)
test('kl7-ei-aRS-40', kl7,
     args: ['-e', '--text', 'HELLO WORLD', '--alphaRingSet', '1 2 3 4 5 6 7 40'],
     should_fail: true, timeout: my_timeout)
test('kl7-ei-aRS-q', kl7,
     args: ['-e', '--text', 'HELLO WORLD', '--alphaRingSet', '1 2 3 4 5 6 7 q'],
     should_fail: true, timeout: my_timeout)
test('kl7-ei-nRN', kl7,
     args: ['-e', '--text', 'HELLO WORLD', '--notchRingNum', '1 2 3 4 5 6 7'],
     timeout: my_timeout)
test('kl7-ei-nRN8', kl7,
     args: ['-e', '--text', 'HELLO WORLD', '--notchRingNum', '1 2 3 4 5 6 7 8'],
     should_fail: true, timeout: my_timeout)
test('kl7-ei-nRN6', kl7,
     args: ['-e', '--text', 'HELLO WORLD', '--notchRingNum', '1 2 3 4 5 6'],
     should_fail: true, timeout: my_timeout)
test('kl7-ei-nRN-0', kl7,
     args: ['-e', '--text', 'HELLO WORLD', '--notchRingNum', '1 2 3 4 5 6 0'],
     should_fail: true, timeout: my_timeout)
test('kl7-ei-nRN-12', kl7,
     args: ['-e', '--text', 'HELLO WORLD', '--notchRingNum', '1 2 3 4 5 6 12'],
     should_fail: true, timeout: my_timeout)
test('kl7-ei-nRN-q', kl7,
     args: ['-e', '--text', 'HELLO WORLD', '--notchRingNum', '1 2 3 4 5 6 q'],
     should_fail: true, timeout: my_timeout)
test('kl7-ei-nRN-dup', kl7,
     args: ['-e', '--text', 'HELLO WORLD', '--notchRingNum', '1 1 3 4 5 6 7'],
     should_fail: true, timeout: my_timeout)
test('kl7-ei-nRS', kl7,
     args: ['-e', '--text', 'HELLO WORLD', '--notchRingSet', 'A B B+ C D E E+'],
     timeout: my_timeout)
test('kl7-ei-nRS8', kl7,
     args: ['-e', '--text', 'HELLO WORLD', '--notchRingSet', 'A B B+ C D E E+ F'],
     should_fail: true, timeout: my_timeout)
test('kl7-ei-nRS6', kl7,
     args: ['-e', '--text', 'HELLO WORLD', '--notchRingSet', 'A B B+ C D E'],
     should_fail: true, timeout: my_timeout)
test('kl7-ei-nRS-F+', kl7,
     args: ['-e', '--text', 'HELLO WORLD', '--notchRingSet', 'A B B+ C D E F+'],
     should_fail: true, timeout: my_timeout)
test('kl7-df-msg1', kl7,
     args :['-d', '--input', '../data/msg_1_cipher_text.txt',
                  '--systemIndicator', '28604',
                  '--rotorCore', 'EHFLIAGB',
                  '--alphaRingSet', '4 28 4 16 9 32 08 11',
                  '--notchRingNum', '5 10 6 7 1 8 3',
                  '--notchRingSet', 'C M+ E B E+ Y K',
                  '--letterCheck', 'ASMTH ISXPI'], timeout: my_timeout)



