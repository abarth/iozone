
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <fs-management/mount.h>
#include <fs-management/ramdisk.h>

int main(int argc, const char** argv) {
  char ramdisk_path[PATH_MAX];
  int rv = create_ramdisk("test-min", ramdisk_path, 512, (1 << 23));
  printf("create_ramdisk => %d: %s\n", rv, ramdisk_path);

  mx_status_t status = mkfs(ramdisk_path, DISK_FORMAT_MINFS, launch_stdio_sync, &default_mkfs_options);
  printf("mkfs(DISK_FORMAT_MINFS) => %d\n", status);

  int dev = open(ramdisk_path, O_RDWR);
  printf("open => %d\n", dev);

  status = mount(dev, "/tmp/minfs", DISK_FORMAT_MINFS, &default_mount_options, launch_stdio_sync);
  printf("mount(DISK_FORMAT_MINFS) => %d\n", status);

  rv = create_ramdisk("test-fat", ramdisk_path, 512, (1 << 23));
  printf("create_ramdisk => %d: %s\n", rv, ramdisk_path);

  status = mkfs(ramdisk_path, DISK_FORMAT_FAT, launch_stdio_sync, &default_mkfs_options);
  printf("mkfs(DISK_FORMAT_FAT) => %d\n", status);

  dev = open(ramdisk_path, O_RDWR);
  printf("open => %d\n", dev);

  status = mount(dev, "/tmp/fatfs", DISK_FORMAT_FAT, &default_mount_options, launch_stdio_sync);
  printf("mount(DISK_FORMAT_FAT) => %d\n", status);

  return 0;
}
