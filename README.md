srtm-gridded-vector
===================

Source
------

```
wget -m -np https://dds.cr.usgs.gov/srtm/version2_1/SRTM30/
```

Tile the world
--------------

```
make
for i in dds.cr.usgs.gov/srtm/version2_1/SRTM30/[ew]*[ns]*; do ./dem2json <(unzip -p $i/$(basename $i).hdr.zip) <(unzip -p $i/$(basename $i).dem.zip); done | time tippecanoe -P -r1 -z9 -f -o srtm.mbtiles
```
