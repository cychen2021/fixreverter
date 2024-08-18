with open('/src/build.sh') as build_f:
    build_script = build_f.read()
build_script = build_script.replace('make', 'bear make')
with open('/src/build.sh', 'w') as build_f:
    build_f.write(build_script)
