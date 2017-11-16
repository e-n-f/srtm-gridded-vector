srtm-gridded-vector
===================

Makes vector tiles of gridded worldwide elevation data

Source data
-----------

[SRTM30](https://dds.cr.usgs.gov/srtm/version2_1/SRTM30/srtm30_documentation.pdf): 30-meter SRTM elevation data, with voids filled by USGS 30-meter topography

```
wget -m -np https://dds.cr.usgs.gov/srtm/version2_1/SRTM30/
```

Tile the world
--------------

```
$ make
$ for i in dds.cr.usgs.gov/srtm/version2_1/SRTM30/[ew]*[ns]*; do ./dem2json <(unzip -p $i/$(basename $i).hdr.zip) <(unzip -p $i/$(basename $i).dem.zip); done | time tippecanoe -P -r1 -z9 -f -o srtm.mbtiles
For layer 0, using name "srtm"
115198929 features, 2177428243 bytes of geometry, 4 bytes of separate metadata, 142873 bytes of string pool
  99.9%  9/64/249
     3907.19 real      9693.81 user       528.80 sys
```

What the GeoJSON looks like
---------------------------

It is represented as points with ~0.025 degree spacing at zoom level 9,
with progressively smaller spacing at lower zooms.

Each point looks like this:

```
{"type": "Feature", "properties":{"elevation":158}, "tippecanoe":{"minzoom":0, "maxzoom": 0}, "geometry": {"type": "Point", "coordinates" : [ 20.004167, 39.995833 ] } }
```

with a `minzoom` and `maxzoom` set so it only appears at one zoom level.
