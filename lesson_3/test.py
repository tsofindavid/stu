import os
import subprocess

stdin = './z2_testing/stdin'
stdout = './z2_testing/stdout'

build = subprocess.run('cmake --build .',  
    shell=True,
    stdout=subprocess.PIPE, 
    stderr=subprocess.PIPE)

if build.returncode != 0:
    print(build.stdout.decode())
    raise BaseException()

passed = 0
failed = 0

tests = os.listdir(stdin)
tests.sort()

for test in tests:
    for scenario in os.listdir(f'{stdin}/{test}'):
        print(f'diff: ./z2 < {stdin}/{test}/{scenario}  | diff - {stdout}/{test}/{scenario} --ignore-trailing-space')       
        output = subprocess.run(
            f'./z2 < {stdin}/{test}/{scenario}  | diff - {stdout}/{test}/{scenario} --ignore-trailing-space', 
            shell=True,
            stdout=subprocess.PIPE, 
            stderr=subprocess.PIPE)
        
        
        if output.returncode == 0 or len(output.stdout.decode()) == 9:
            passed +=1
            print("✅ Test passed")
            print(output.stdout.decode())
        else:
            failed+=1
            print("❌ Test failed")
            print(output.stdout.decode())


    print(f'passed ✅: {passed}')
    print(f'failed ❌: {failed}')
    print('--------------------------')
