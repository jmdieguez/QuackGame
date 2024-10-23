#include <atomic>
#include <vector>
#include <cstdint>

#include "../../common/thread.h"
#include "../../common/queue.h"
// #include "../../common/actions.h"
#include "../../common/snapshots.h"
#include "protocol.h"

class Network : public Thread
{
private:
    std::atomic<bool> &keep_running;
    Queue<std::vector<Snapshot>> &queue_receiver;
    // Queue<ActionMessage> &queue_sender;
    Queue<std::vector<uint8_t>> &queue_sender;
    ClientProtocol protocol;
    bool send_message();
    void sender_message();
    bool receive_message();

public:
    // explicit Network(std::atomic<bool> &keep_running, Queue<std::vector<Snapshot>> &queue_receiver, Queue<ActionMessage> &queue_sender);
    explicit Network(std::atomic<bool> &keep_running, Queue<std::vector<Snapshot>> &queue_receiver, Queue<std::vector<uint8_t>> &queue_sender);
    virtual void run() override;
    ~Network();
};
