int trap(int* height, int heightSize) {

    int i, j, count = 0;
    void go_left(int*, int, int*, int);
    void go_right(int*, int, int*, int);
    int accleft[heightSize], accright[heightSize];
    
    for (i = 0, j= heightSize - 1; i < heightSize; i++, j--) {
        go_left(height, heightSize, accleft, i);
        go_right(height, heightSize, accright, j);
    }
    go_left(0, 0, 0, -1);
    go_right(0, 0, 0, -1);

    /*
    for (i = 0; i < heightSize; i++)
        printf("%d, ", accleft[i]);
    printf("\n");
    for (i = 0; i < heightSize; i++)
        printf("%d, ", accright[i]);
    printf("\n");
    */
    for (i = 0; i< heightSize; i++) {
        if (accleft[i] && accright[i])
            count += accleft[i];
        else if (accleft[i])
            count += accleft[i];
        else if (accright[i])
            count += accright[i];
    }

    return count;
}

void go_left(int* height, int heightSize, int* acc, int i) {
    
    static int tip1 = 0, tip2 = 0;
    int j;
    
    if (i == -1) {
        tip1 = tip2 = 0;
        return;
    }

    if (height[i] < tip1) {
        acc[i] = tip1 - height[i];
        tip2 = height[i];
    }
    
    if (height[i] >= tip1)
        acc[i] = 0;

    if (height[i] > tip1)
        tip1 = height[i];
    else if (height[i] < tip2) {
        tip1 = tip2;
        acc[i-1] = 0;
    }

    if (i == heightSize - 1) {
        for (j = i; j > -1 && acc[j] != 0; j--)
            acc[j] = 0;
    }
}

void go_right(int* height, int heightSize, int* acc, int i) {
    
    static int tip1 = 0, tip2 = 0;
    int j;

    if (i == -1) {
        tip1 = tip2 = 0;
        return;
    }

    if (height[i] < tip1) {
        acc[i] = tip1 - height[i];
        tip2 = height[i];
    }
    
    if (height[i] >= tip1)
        acc[i] = 0;

    if (height[i] > tip1)
        tip1 = height[i];
    else if (height[i] < tip2) {
        tip1 = tip2;
        acc[i+1] = 0;
    }

    if (i == 0) {
        for (j = i; j < heightSize && acc[j] != 0; j++)
            acc[j] = 0;
    }
}
