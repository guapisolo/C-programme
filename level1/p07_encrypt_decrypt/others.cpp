#ifndef BASE64PP_H_
#define BASE64PP_H_

#include <stdexcept>
#include <string>
#include <vector>

#ifndef _WIN32
#define NOEXCEPT noexcept
#else
#define NOEXCEPT
#endif

namespace base64pp {

	static const char* kEncoding =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

class Base64 {
public:
    /** Base64-encode the string. */
    static std::string encode(std::string const& data) NOEXCEPT;

    /** Decode base64-encoded string, throwing on error. */
    static std::string decode(std::string const& data);

    static uint8_t decode_char(char c) {
        if (c >= 'A' && c <= 'Z') {
            return c - 'A';
        } else if (c >= 'a' && c <= 'z') {
            return c - 'a' + 26;
        } else if (c >= '0' && c <= '9') {
            return c - '0' + 52;
        } else if (c == '+') {
            return 62;
        } else if (c == '/') {
            return 63;
        } else {
            throw std::runtime_error("Invalid encoding");
        }
    }
private:

};

template<typename Integral, int Bits>
class BitWriter {
public:
    void append(Integral value) {
        int remain = Bits;
        while (remain > 0) {
            if (avail_ == 0) {
                data_.push_back(0);
                avail_ = 8;
            }

            auto take = std::min(remain, avail_);
            auto shift = avail_ - take;
            auto drop = remain - take;

            data_.back() |= ((value >> drop) << shift);

            remain -= take;
            avail_ -= take;
        }
    }

    std::string to_string() const {
        // Only returning fully written bytes
        return avail_ == 0 ? std::string(data_.begin(), data_.end()) :
            std::string(data_.begin(), data_.end() - 1);
    }
private:
    int avail_ = 0;
    std::vector<char> data_;
};


//从字节中取Bits位（Bits位为一个单元,如base64每6位为1个单元)
template<typename Integral, int Bits>
class BitStream {
public:
    explicit BitStream(std::string const& data) : data_(data) {
        if (data_.size() > 0) {
            avail_ = 8;
        }
    }
    //每次调用next则取一个单元
    Integral next(bool *more) 
    {
        Integral ret = 0;
        int needed = Bits;
        //0 needed为0则表示一个完整的单元已经取完了
        while (needed > 0) 
        {
            // Number of bits to use from the current value
            //此处一个std::min()已经把一个单元数大于或者小于8的情况给包含了
            //1 每次取多少位 take
            auto take = std::min(needed, avail_);

            // Shift over to accumulator's leftmost available position
            //2 每次往左移动多少位 shift
            auto shift = needed - take;
            
            //下面将要取take位,接着左移shift位(shift + take = needed一个完整的单元)
            // Get the high [take] bits from the current value
            //接着取当前字节的take位(从高位往低位取)
            uint8_t interesting = (data_[idx_] >> (avail_ - take)) & ((1 << take) - 1);

            //以Bits为一个单元移动shift位到最高位
            ret |= (interesting << shift);
            //3 Bits(模板传入)个比特位一个单元，这个单元还剩多少为没取
            needed -= take;
            //4 当前这个字节还剩多少位没取
            avail_ -= take;
            //5 取完了一个字节后移动到下一个字节，avail_重新置为8
            if (avail_ == 0) 
            {
                if (++idx_ == data_.size()) 
                {
                    *more = false;
                    return ret;
                }
                avail_ = 8;
            }
        }
        *more = true;
        return ret;
    }
private:
    size_t idx_ = 0;
    int avail_ = 0;
    std::string const& data_;
};

inline std::string Base64::encode(std::string const& data) NOEXCEPT {
    if (data.empty()) {
        return std::string();
    }

    size_t bits = data.size() * 8;
    uint8_t rchars = (bits % 24) / 8;
    //字符串编码后的长度
    size_t storage = (bits / 24) * 4 + (rchars == 0 ? 0 : 4);

    bool more = false;
    BitStream<uint8_t, 6> bs(data);

    std::vector<char> ret(storage);
    auto iter = ret.begin();
    do {
        uint8_t bits = bs.next(&more);
        (*iter++) = kEncoding[bits];
    } while (more);

    //计算填充`=`号的个数
    if (rchars > 0) {
        for (int i = 0; i < 3 - rchars; ++i) {
            (*iter++) = '=';
        }
    }

    return std::string(ret.begin(), ret.end());
}

inline std::string Base64::decode(std::string const& data) {
    if (data.empty()) {
        return std::string();
    }

    auto rit = data.rbegin();
    int eq = 0;
    while (*rit++ == '=') {
        if (++eq > 2) {
            throw std::runtime_error("Invalid encoding");
        }
    }

    BitWriter<uint8_t, 6> writer;
    for (unsigned int i = 0; i < data.size() - eq; ++i) {
        uint8_t bits = decode_char(data[i]);
        writer.append(bits);
    }
    return writer.to_string();
}

} // base64pp namespace

#endif // BASE64PP_H_
