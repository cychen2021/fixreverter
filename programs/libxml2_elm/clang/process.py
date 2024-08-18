with open('/src/build.sh') as build_f:
    build_script = build_f.readlines()
build_script = [l.replace('make', 'bear make') for l in build_script[:32]]
with open('/src/build.sh', 'w') as build_f:
    build_f.writelines(build_script)
