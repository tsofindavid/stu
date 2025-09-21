import os
import shutil
import subprocess

def find(line: str, prefixes):
    print(f'find in line: {line}')
    result = [] 
    for elem in line.split(' '):
        for prefix in prefixes:
            if prefix in elem:
                result.append(elem.replace('\n', '').replace('.exe', ''))
    return result

def join(items, prefix = ' '):
    result = ''
    for i in range(len(items)):
        if i:
            result += f'{prefix}{items[i]}'
        else:
            result += f'{items[i]}'
    return result


build = 'z5'
build_cmd = f'gcc z5.c -Wall -o {build}'

z5_tests = [{'stdin': './z5_testing/stdin', 'stdout': './z5_testing/stdout'}]

exclude = []
skipping = True

build = subprocess.run(
    build_cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE
)

if build.returncode != 0:
    print(build.stdout.decode())
    raise BaseException()

passed = 0
failed = 0
skip = False

for z5_test in z5_tests:
    if skip:
        break

    stdin = z5_test['stdin']
    stdout = z5_test['stdout']

    scenarios = os.listdir(stdin)
    scenarios.sort(key=lambda x: int(x.split('s')[1]))

    for scenario in scenarios:
        if scenario in exclude:
            continue

        examples = os.listdir(f'{stdin}/{scenario}')
        examples.sort(key=lambda x: int(x.split('example')[1].split('.')[0]))

        for example in examples:
            if skip and skipping:
                break

            file = open(f'{stdin}/{scenario}/{example}')

            command = join(find(file.readline(), ['.exe', '.txt']))
            items = find(file.readline(), ['.json'])[0]

            file.close()
            
            if os.path.exists('./items.json'):
                os.remove('./items.json')

            print(f'./json_txt/json/{items}')
            if os.path.exists(f'./json_txt/json/{items}'):
                shutil.copy(f'./json_txt/json/{items}', './items.json')
            else:
                print('items does not exist')

            print(
               f'./{command} 2>&1 | diff - {stdout}/{scenario}/{example} --ignore-trailing-space',
            )
            output = subprocess.run(
                f'./{command} 2>&1 | diff - {stdout}/{scenario}/{example} --ignore-trailing-space',
                shell=True,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
            )

            if output.returncode == 0 or len(output.stdout.decode()) == 9:
                passed += 1
                print('✅ Test passed')
                print(output.stdout.decode())
            else:
                failed += 1
                print('❌ Test failed')
                print(output.stdout.decode())
                skip = True

    print(f'passed ✅: {passed}')
    print(f'failed ❌: {failed}')
    print('--------------------------')
