with open('/src/build.sh') as build_f:
    build_script = build_f.readlines()
new_build_script = []
for line in build_script[:31]:
    line = line.replace('make', 'bear make') \
               .replace('autogen.sh', 'configure') \
               .replace('--disable-shared', '--enable-shared=no')
    if line.strip().startswith('--without'):
        line = line.replace('--without', '--with').replace(' \\', '=off \\')
    new_build_script.append(line)
with open('/src/build.sh', 'w') as build_f:
    build_f.writelines(new_build_script)
