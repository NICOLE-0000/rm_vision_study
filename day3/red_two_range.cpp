// 红色分两段提取
Mat hsv;
cvtColor(img, hsv, COLOR_BGR2HSV);

Mat mask1, mask2, mask_red;

// 第一段：H 0-10（正红附近）
inRange(hsv, Scalar(0,   s_min, v_min), Scalar(10, 255, 255), mask1);

// 第二段：H 160-180（偏紫的红）
inRange(hsv, Scalar(160, s_min, v_min), Scalar(180, 255, 255), mask2);

// 合并两段
bitwise_or(mask1, mask2, mask_red);

imshow("Red Mask", mask_red);