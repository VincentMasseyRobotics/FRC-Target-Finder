import os

os.system("cmake unix/.")
os.system("make -C unix/.")
os.system("unix/StrongholdTracking")
