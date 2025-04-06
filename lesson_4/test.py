import os
import subprocess

build = subprocess.run('make build',  
    shell=True,
    stdout=subprocess.PIPE, 
    stderr=subprocess.PIPE)

if build.returncode != 0:
    print(build.stdout.decode())
    raise BaseException()

passed = 0
failed = 0

z3_tests = [{
    "stdin": './z3_testing/stdin',
    "stdout": './z3_testing/stdout'
},
{
    "stdin": './z3_testing_extra/stdin',
    "stdout": './z3_testing_extra/stdout'
}]

skip = False

for z3_test in z3_tests:
    if skip:
        break

    stdin = z3_test['stdin']
    stdout = z3_test['stdout']

    tests = os.listdir(stdin)
    tests.sort(key=lambda x: int(x.split('_')[1]))

    for test in tests:
        if skip:
            break

        scenarios = os.listdir(f'{stdin}/{test}')
        scenarios.sort(key=lambda x: int(x.split('_')[1].split('.')[0]))

        for scenario in scenarios:
            if skip:
                break

            print(f'diff: ./z3 < {stdin}/{test}/{scenario}  | diff - {stdout}/{test}/{scenario} --ignore-trailing-space')       
            output = subprocess.run(
                f'./z3 < {stdin}/{test}/{scenario}  | diff - {stdout}/{test}/{scenario} --ignore-trailing-space', 
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
                skip = True;


        print(f'passed ✅: {passed}')
        print(f'failed ❌: {failed}')
        print('--------------------------')
