SUBDIRS = guide design

EXTRA_DIST = version.ent.in differences.txt Doxyfile Doxyfile-xml

nobase_dist_doc_DATA  = examples/kea4/single-subnet.json
nobase_dist_doc_DATA += examples/kea4/several-subnets.json
nobase_dist_doc_DATA += examples/kea6/simple.json
nobase_dist_doc_DATA += examples/kea6/several-subnets.json
nobase_dist_doc_DATA += examples/ddns/sample1.json
nobase_dist_doc_DATA += examples/ddns/template.json

devel:
	mkdir -p html
	(cat Doxyfile; echo PROJECT_NUMBER=$(PACKAGE_VERSION)) | doxygen - > html/doxygen.log 2> html/doxygen-error.log
	echo `grep -i ": warning:" html/doxygen-error.log | wc -l` warnings/errors detected.

guide:
	$(MAKE) -C guide kea-guide.html

clean:
	rm -rf html

# That's a bit of a hack, but we are making sure that devel target
# is always valid. The alternative is to make devel depend on all
# *.cc *.h files in the whole tree.
.PHONY: devel guide
