class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        double res = 0.0;
        int cnt;
        int target_j;
        int j;
        int s1, s2;
        int i1, i2;
        if(nums1.size() == 0) {
            /* find in nums2 */
            s2 = nums2.size();
            if(s2 == 0) return 0.0;
            if(s2 % 2 == 0) {
                res += nums2[s2/2-1] + nums2[s2/2];
                return res/2.0;
            } else {
                return (double)nums2[s2/2];
            }
        }
        if(nums2.size() == 0) {
            /* find in nums1 */
            s1 = nums1.size();
            if(s1 == 0) return 0.0;
            if(s1 % 2 == 0) {
                res += nums1[s1/2-1] + nums1[s1/2];
                return res/2.0;
            } else {
                return (double)nums1[s1/2];
            }
        }
        
        /* neither nums1 nor nums2 are empty */
        s1 = nums1.size();
        s2 = nums2.size();
        cnt = s1 + s2;
        target_j = cnt/2;
        i1 = 0;
        i2 = 0;
        while(i1 < s1 || i2 < s2) {
            if(i1 == s1) {
                /* read nums2 only */
                if(cnt % 2 == 0) {
                    if(j <= target_j -1) {
                        i2 += target_j - j;
                        res = nums2[i2] + nums2[i2-1];
                        res /= 2.0;
                    } 
                    if(j == target_j) {
                        i2 += target_j - j;
                        res += nums2[i2];
                        res /= 2.0;
                    }
                } else {
                    i2 += target_j - j;
                    res = nums2[i2];
                }
                break;
            }
            if(i2 == s2) {
                /* read nums1 only */
                if(cnt % 2 == 0) {
                    if(j <= target_j -1) {
                        i1 += target_j - j;
                        res = nums1[i1] + nums1[i1-1];
                        res /= 2.0;
                    } 
                    if(j == target_j) {
                        i1 += target_j - j;
                        res += nums1[i1];
                        res /= 2.0;
                    }
                } else {
                    i1 += target_j - j;
                    res = nums1[i1];
                }
                break;
            }
            if(cnt % 2 == 0) {
                if(j == target_j - 1) {
                    res = nums1[i1] < nums2[i2]? nums1[i1] : nums2[i2];
                }
                if(j == target_j) {
                    res += nums1[i1] < nums2[i2]? nums1[i1] : nums2[i2];
                    res /= 2.0;
                    break;
                }
            } else {
                if(j == target_j) {
                    res = nums1[i1] < nums2[i2]? nums1[i1] : nums2[i2];
                    break;
                }
            }
            /* read nums1 and nums2 */
            if(nums1[i1] <= nums2[i2]) {
                i1 += 1;
                j += 1;
            } else {
                i2 += 1;
                j += 1;
            }
            continue;
        }
        
        return res;
    }
};
