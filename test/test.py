import subprocess
import os
import filecmp

def test_suite():
    build()
    os.remove("../src/adventure.log")
    os.remove("output.log")
    run_test("../test/map.csv", "../test/movements.txt")

def build():
    subprocess.call(["make", "clean"], cwd="../src")
    subprocess.call(["make"], cwd="../src")

def run_test(map, movements, log, std):
    invoke_valgrind = ["valgrind", "--leak-check=full", "-v", "--log-file=../test/valgrind.log", "--error-exitcode=1"]
    arg_pipe = [map, movements, "&>>", "../test/output.log"]
    normal_ret = subprocess.call( invoke_valgrind + "./TreasureHunter" + arg_pipe, cwd="../src", shell=True)
    log_ret = subprocess.call( invoke_valgrind + "./TreasureHunterLog" + arg_pipe, cwd="../src", shell=True )
    ai_ret = subprocess.call( invoke_valgrind + "./TreasureHunterAI" + arg_pipe, cwd="../src", shell=True )
    if (normal_ret == 1 or log_ret == 1 or ai_ret == 1):
        print("A memory error occured. map=" +map + " movements=" + movements)
    if not filecmp.cmp("output.log", log):
        print("Unexpected log.")
    if not filecmp.cmp("../src/adventure.log", log):
        print("Unexpected output.")

if __name__ == "__main__":
    test_suite()
