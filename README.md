# Bloaty

Bloaty is a tiny C program that just consumes a given amount of RAM per second.
It can be used to test memory limits and OOM killers.

## Usage

```
make
cc -O2 -Wall -o bloaty bloaty.c
./bloaty
[2019-01-08 14:05:03 UTC] Going to eat 1.00 MiB per second...
[2019-01-08 14:05:03 UTC] Consumed 1.00 MiB so far.
[2019-01-08 14:05:04 UTC] Consumed 2.00 MiB so far.
[2019-01-08 14:05:05 UTC] Consumed 3.00 MiB so far.
[2019-01-08 14:05:06 UTC] Consumed 4.00 MiB so far.
[2019-01-08 14:05:07 UTC] Consumed 5.00 MiB so far.
...
```

Allowed units are K, M, Ki and Mi. If no unit is given, amount is in bytes.

A Docker image is provided as well:

```
docker run --rm xrstf/bloaty 5Mi
```
