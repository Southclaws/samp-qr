#define RUN_TESTS

#include <a_samp>
#include <YSI_Core\y_testing>

#include "qr"

main() {
    AddPlayerClass(101, 0.0, 0.0, 3.5, 0.0, 0, 0, 0, 0, 0, 0);
}

Test:GetMatrix() {
    new out[25 * 25];
    new ret = QR_GetMatrix("https://github.com/Southclaws/", out);
    printf("ret: %d", ret);
    printf("res: '%s'", out);
}


public OnPlayerSpawn(playerid) {
    new Float:X = 10.0;
    new Float:Y = 10.0;
    new Float:Z = 3.5;

    new Float:C_X = X - (QR_PIXEL_GRID_OFFSET * QR_DIMENSIONS) / 2;
    new Float:C_Y = Y - (QR_PIXEL_GRID_OFFSET * QR_DIMENSIONS) / 2;

    new matrix[25 * 25];
    QR_GetMatrix("https://github.com/Southclaws/", matrix);

    new QRGrid:grid[QR_DIMENSIONS][QR_DIMENSIONS];
    QR_CreateGrid(playerid, 0, grid, C_X, C_Y, Z);
    QR_ApplyMatrix(matrix, grid);

    SetPlayerCameraPos(playerid, X, Y, Z + 5.0);
    SetPlayerCameraLookAt(playerid, X, Y + 0.1, Z);

    return 1;
}