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

What the GeoJSON looks like
---------------------------

It is represented as points with ~0.025 degree spacing at zoom level 9,
with progressively smaller spacing at lower zooms.

Each point looks like this:

```
{"type": "Feature", "properties":{"elevation":158.000000}, "tippecanoe":{"minzoom":0, "maxzoom": 0}, "geometry": {"type": "Point", "coordinates" : [ 20.004167, 39.995833 ] } }
```

with a `minzoom` and `maxzoom` set so it only appears at one zoom level.
