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
const QR_ARRAY_SIZE = (QR_DIMENSIONS * QR_DIMENSIONS) + 1;

const QR_PIXEL_OBJECT_BLACK = 3106;
const QR_PIXEL_OBJECT_WHITE = 3003;
const Float:QR_PIXEL_GRID_OFFSET = 0.008; // place the "pixels" this far apart

// QR_CreateGrid 
stock QR_CreateGrid(
    playerid,
    worldid,
    const matrix[],
    QRGrid:grid[QR_DIMENSIONS][QR_DIMENSIONS],
    Float:x = 0.0,
    Float:y = 0.0,
    Float:z = 1000.0
) {
    for(new ix = 0; ix < QR_DIMENSIONS; ++ix) {
        for(new iy = 0; iy < QR_DIMENSIONS; ++iy) {
            grid[ix][iy] = QRGrid:CreateDynamic3DTextLabel(
                "@",
                matrix[ix + iy * (QR_DIMENSIONS)] == '0' ?
                    QR_PIXEL_OBJECT_BLACK :
                    QR_PIXEL_OBJECT_WHITE,
                x + (QR_PIXEL_GRID_OFFSET * ix),
                y + (QR_PIXEL_GRID_OFFSET * iy),
                z,
                20.0,
                INVALID_PLAYER_ID,
                INVALID_VEHICLE_ID,
                0,
                worldid,
                -1,
                playerid
            );
        }
    }

    return;
}
