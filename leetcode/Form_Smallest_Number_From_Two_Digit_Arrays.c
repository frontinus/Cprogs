int minNumber(int* nums1, int nums1Size, int* nums2, int nums2Size){
    int longl,shtl,flag2=INT_MAX,flag=INT_MAX,i,j,final=INT_MAX,flagg=0;
    if(nums1Size>nums2Size){
        longl = nums1Size;
        shtl = nums2Size;
        for(i =0;i<longl;i++){
            if(flag>nums1[i]){
                flag = nums1[i];
            }
            for(j =0;j<shtl;j++){
                if(nums1[i] == nums2[j]){
                    if(final>nums1[i]){
                        final =nums1[i];
                        flagg =1;
                    }
                }
                if(flag2>nums2[j]){
                    flag2 = nums2[j];
                }
            }
        }
    }
    else{
        longl = nums2Size;
        shtl = nums1Size;
        for(i =0;i<longl;i++){
            if(flag>nums2[i]){
                flag = nums2[i];
            }
            for(j =0;j<shtl;j++){
                if(nums1[j] == nums2[i]){
                    if(final>nums2[i]){
                        final =nums2[i];
                        flagg =1;
                    }
                }
                if(flag2>nums1[j]){
                    flag2 = nums1[j];
                }
            }
        }
    }
    if(flagg==1){
        return final;
    }
    if (flag2<flag){
        final= flag2*10 + flag;
    }
    else{
        if(flag2 ==flag){
            final = flag2;
        }
        else{
            final= flag*10 + flag2;   
        }
    }
    return final;
}