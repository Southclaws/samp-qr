#define RUN_TESTS

#include <a_samp>
#include <YSI_Core\y_testing>

#include "qr"

main() {
    AddPlayerClass(101, 0.0, 0.0, 3.5, 0.0, 0, 0, 0, 0, 0, 0);
    Streamer_SetMaxItems(STREAMER_TYPE_OBJECT, 1000);
}

Test:GetMatrix() {
    new out[QR_ARRAY_SIZE];
    new ret = QR_GetMatrix("https://southcla.ws/", out);
    printf("ret: %d", ret);
    printf("res: '%s'", out);
}


public OnPlayerSpawn(playerid) {
    new Float:X = 10.0;
    new Float:Y = 10.0;
    new Float:Z = 3.5;

    new Float:C_X = X - (QR_PIXEL_GRID_OFFSET * QR_DIMENSIONS) / 2;
    new Float:C_Y = Y - (QR_PIXEL_GRID_OFFSET * QR_DIMENSIONS) / 2;

    new matrix[QR_ARRAY_SIZE];
    new ret = QR_GetMatrix("https://github.com/Southclaws/", matrix);

    printf("%d matrix: [%s]", ret, matrix);

    new QRGrid:grid[QR_DIMENSIONS][QR_DIMENSIONS];
    QR_CreateGrid(playerid, 0, matrix, grid, C_X, C_Y, Z);

    SetPlayerPos(playerid, X, Y + 10, Z + 2.0);
    SetPlayerCameraPos(playerid, X, Y, Z + 1.0);
    SetPlayerCameraLookAt(playerid, X, Y + 0.1, Z);

    CreateDynamicObject(19362, X, Y, Z, 0.0, 90.0, 0.0);

    return 1;
}