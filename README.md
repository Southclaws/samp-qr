# samp-qr

For QR codes.

```c
    new matrix[QR_ARRAY_SIZE];
    new ret = QR_GetMatrix("https://github.com/Southclaws/", matrix);
```

Fills `matrix` with a set of either '0' or '1'. The matrix is a simple row-by-row representation of a grid of black or white pixels.

Then you can render it however you like.

`QR_CreateGrid` is a helper that uses pool balls, but unfortunately SA-MP has an object limit so it won't work.
