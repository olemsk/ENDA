.PHONY:game
game:
	ptxdist drop game compile
	ptxdist compile game
	
.PHONY:gameup
gameup:
	ptxdist targetinstall game
	ptxdist image root.romfs
	ptxdist test flash-rootfs

.PHONY:pad
pad:
	ptxdist drop driver-gamepad prepare
	ptxdist go

.PHONY:padup
padup:
	ptxdist targetinstall driver-gamepad
	ptxdsit image root.romfs
	ptxdist test flash-rootfs
#
# Committer: Hermann Sundklakk <hermansu@dmlab03.(none)>

