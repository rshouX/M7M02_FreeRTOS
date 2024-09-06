rm -f *.uvgui.*
rm -rf Kernel/Project/DebugConfig Kernel/Project/Listing Kernel/Project/Object
rm -rf Monitor/Project/DebugConfig Monitor/Project/Listing Monitor/Project/Object
rm -rf Proc1/Project/DebugConfig Proc1/Project/Listing Proc1/Project/Object
rm -rf Proc2/Project/DebugConfig Proc2/Project/Listing Proc2/Project/Object
rm -rf Virt1/Project/DebugConfig Virt1/Project/Listing Virt1/Project/Object

rm -rf Kernel/Project/*.uvguix.* Kernel/Project/*.uvoptx
rm -rf Monitor/Project/*.uvguix.* Monitor/Project/*.uvoptx Monitor/Project/*_image.c
rm -rf Proc1/Project/*.uvguix.* Proc1/Project/*.uvoptx Proc1/Project/*_image.c
rm -rf Proc2/Project/*.uvguix.* Proc2/Project/*.uvoptx Proc2/Project/*_image.c
rm -rf Virt1/Project/*.uvguix.* Virt1/Project/*.uvoptx Virt1/Project/*_image.c