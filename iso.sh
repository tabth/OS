mkdir -p build/iso_root

cd src
make -C limine

make -C kernel

cp -v kernel/kernel.elf limine/limine.sys \
    limine/limine-cd.bin limine/limine-cd-efi.bin limine.cfg ../build/iso_root 

./limine/limine-deploy ../build/image.iso

cd ../build

xorriso -as mkisofs -b limine-cd.bin \
    -no-emul-boot -boot-load-size  -boot-info-table \
    --efi-boot limine-cd-efi.bin \
    -efi-boot-part --efi-boot-image --protective-msdos-label \
    iso_root -o image.iso

qemu-system-x86_64 -M q35 -m 2G -bios OVMFbin/OVMF_CODE-pure-efi.fd -cdrom image.iso -boot d 