import subprocess

result = subprocess.run(["ldd", "car-racing"], stdout=subprocess.PIPE)
deps = result.stdout

deps = [d.decode("utf-8") for d in deps.splitlines()]

libs = []
for line in deps:
    if len(line.split("=>")) == 2:
        libs.append(line.split("=>")[1])

libs = [d.strip() for d in libs]
libs = [d.split()[0] for d in libs]
for line in libs:
    print(line)

