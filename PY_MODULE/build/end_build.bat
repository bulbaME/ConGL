@echo off
move build.dll ../congl/bin/
cd ../congl/bin/
FOR /F "USEBACKQ" %%F IN (`%* -c "from distutils import sysconfig; print(sysconfig.get_config_var('EXT_SUFFIX'))"`) DO ( move build.dll congl%%F )