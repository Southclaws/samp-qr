// built-in include guard removal
// just in case the user has a local dependency with the same file name
#if defined _inc_qr
	#undef _inc_qr
#endif
// custom include-guard to ensure we don't duplicate
#if defined _qr_included
	#endinput
#endif
#define _qr_included

#include <streamer>

// -
// Natives
// -

// QR_GetMatrix encodes `input` as a flattened QR code matrix of characters '0'
// and '1', where '0' represents black and '1' represents white.
// Input must be <= 47 characters.
native QR_GetMatrix(const input[], output[], length = sizeof output);

// -
// Rendering
// -

const QR_DIMENSIONS = 25;
const QR_ARRAY_SIZE = QR_DIMENSIONS * QR_DIMENSIONS;

const QR_PIXEL_OBJECT = 19811; // a burger box, nice and square
const Float:QR_PIXEL_GRID_OFFSET = 0.2; // place the "pixels" this far apart

// QR_CreateGrid 
stock QR_CreateGrid(
    playerid,
    worldid,
    QRGrid:grid[QR_DIMENSIONS][QR_DIMENSIONS],
    Float:x = 0.0,
    Float:y = 0.0,
    Float:z = 1000.0
) {
    for(new ix = 0; ix < QR_DIMENSIONS; ++ix) {
        for(new iy = 0; iy < QR_DIMENSIONS; ++iy) {
            grid[ix][iy] = QRGrid:CreateDynamicObject(
                19811,
                x + (QR_PIXEL_GRID_OFFSET * ix),
                y + (QR_PIXEL_GRID_OFFSET * iy),
                z,
                0.0, 0.0, 0.0,
                worldid, -1, playerid);
        }
    }

    return;
}
stock QR_ApplyMatrix(
    const matrix[],
    const QRGrid:grid[QR_DIMENSIONS][QR_DIMENSIONS]
) {
    for(new x = 0; x < QR_DIMENSIONS; ++x) {
        for(new y = 0; y < QR_DIMENSIONS; ++y) {
            SetDynamicObjectMaterial(
                _:grid[x][y], 0, 18646,
                "matcolours", "white",
                matrix[x + y * (QR_DIMENSIONS)] ?
                    0xFFFFFFFF :
                    0x00000000
            );
        }
    }
}
