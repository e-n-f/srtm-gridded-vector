srtm-gridded-vector
===================

Source
------

```
wget -m -np https://dds.cr.usgs.gov/srtm/version2_1/SRTM30/
```

One tile
--------

```
make
./dem2json <(unzip -p dds.cr.usgs.gov/srtm/version2_1/SRTM30/e020n40/e020n40.hdr.zip ) <(unzip -p dds.cr.usgs.gov/srtm/version2_1/SRTM30/e020n40/e020n40.dem.zip ) | tippecanoe -P -r1 -z9 -f -o foo.mbtiles
```
