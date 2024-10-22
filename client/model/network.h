#include <atomic>
#include <vector>
#include <cstdint>

#include "../../common/thread.h"
#include "../../common/queue.h"

class Network : public Thread
{
private:
    // socket
    std::atomic<bool> &keep_running;
    Queue<std::vector<uint8_t>> &queue_receiver;
    Queue<std::vector<uint8_t>> &queue_sender;

    bool send_message();
    void sender_message();
    bool receive_message();

public:
    explicit Network(std::atomic<bool> &keep_running, Queue<std::vector<uint8_t>> &queue_receiver, Queue<std::vector<uint8_t>> &queue_sender);
    virtual void run() override;
    ~Network();
};
