import subprocess

def test_suite():
    subprocess.Popen(["make clean && make"], cwd="../src")

if __name__ == "__main__":
    test_suite()
