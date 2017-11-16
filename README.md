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
$ make
$ for i in dds.cr.usgs.gov/srtm/version2_1/SRTM30/[ew]*[ns]*; do ./dem2json <(unzip -p $i/$(basename $i).hdr.zip) <(unzip -p $i/$(basename $i).dem.zip); done | time tippecanoe -P -r1 -z9 -f -o srtm.mbtiles
115201710 features, 2135447250 bytes of geometry, 4 bytes of separate metadata, 140594 bytes of string pool
  99.9%  9/432/153
     3789.21 real      9566.32 user       532.21 sys
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
