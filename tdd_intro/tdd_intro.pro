TEMPLATE = subdirs

SUBDIRS += \
    3rd_party \
    demo \
    homework \
    cleanroom

demo.depends = 3rd_party
homework.depends = 3rd_party
workshops.depends = 3rd_party
cleanroom.depends = 3rd_party
