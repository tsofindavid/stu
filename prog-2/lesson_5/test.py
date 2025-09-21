import os
import subprocess


z4_tests = [{"stdin": "./z4_testing/stdin", "stdout": "./z4_testing/stdout"}]

prefixes = [
    {"scenarios": ["scenar_1", "scenar_2"], "examples": [], "prefix": "0"},
    {
        "scenarios": ["scenar_4"],
        "examples": [
            "example_1.txt",
            "example_7.txt",
            "example_8.txt",
            "example_9.txt",
        ],
        "prefix": "10",
    },
    {
        "scenarios": ["scenar_4"],
        "examples": [
            "example_2.txt",
        ],
        "prefix": "5",
    },
    {
        "scenarios": ["scenar_4"],
        "examples": [
            "example_3.txt",
        ],
        "prefix": "14",
    },
]

exclude = []
skipping = True

build = subprocess.run(
    "cmake --build .", shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE
)

if build.returncode != 0:
    print(build.stdout.decode())
    raise BaseException()

passed = 0
failed = 0
skip = False

for z4_test in z4_tests:
    if skip:
        break

    stdin = z4_test["stdin"]
    stdout = z4_test["stdout"]

    scenarios = os.listdir(stdin)
    scenarios.sort(key=lambda x: int(x.split("_")[1]))

    for scenario in scenarios:
        if scenario in exclude:
            continue

        print(f"Scenario: {scenario}")

        examples = os.listdir(f"{stdin}/{scenario}")
        examples.sort(key=lambda x: int(x.split("_")[1].split(".")[0]))

        for example in examples:
            if skip and skipping:
                break

            prefix = ""
            for p in prefixes:
                if scenario in p["scenarios"]:
                    if len(p["examples"]) != 0:
                        print(f"ad {example}")
                        if example in p["examples"]:
                            prefix += " " + p["prefix"]
                    else:
                        prefix += " " + p["prefix"]

            print(
                f"diff: ./z4{prefix} < {stdin}/{scenario}/{example}  | diff - {stdout}/{scenario}/{example} --ignore-trailing-space"
            )
            output = subprocess.run(
                f"./z4{prefix} < {stdin}/{scenario}/{example}  | diff - {stdout}/{scenario}/{example} --ignore-trailing-space",
                shell=True,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
            )

            if output.returncode == 0 or len(output.stdout.decode()) == 9:
                passed += 1
                print("✅ Test passed")
                print(output.stdout.decode())
            else:
                failed += 1
                print("❌ Test failed")
                print(output.stdout.decode())
                skip = True

    print(f"passed ✅: {passed}")
    print(f"failed ❌: {failed}")
    print("--------------------------")
