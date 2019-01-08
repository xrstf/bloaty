# Bloaty

Bloaty is a tiny C program that just consumes a given amount of RAM per second.
It can be used to test memory limits and OOM killers.

## Usage

```
make
./bloaty [amount=1Mi]
```

Allowed units are K, M, Ki and Mi. If no unit is given, amount is in bytes.

A Docker image is provided as well:

```
docker run --rm xrstf/bloaty 5Mi
```
