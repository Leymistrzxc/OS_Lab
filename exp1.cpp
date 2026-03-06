class TT {
private:
    std::vector<std::vector<std::queue<std::shared_ptr<CC>>>> queues;
    std::vector<int> timeQuantum;
    std::vector<int> agingThreshold;

    int YY(AA t) const {
        return (t == AA::SYSTEM) ? 0 : (t == AA::INTERACTIVE) ? 1 : 2;
    }

public:
    TT(int numLevels, const std::vector<int>& quanta, const std::vector<int>& aging)
        : timeQuantum(quanta), agingThreshold(aging) {
        queues.resize(3); // 3 process types
        for (auto& typeQueues : queues) {
            typeQueues.resize(numLevels);
        }
    }

    void OO(std::shared_ptr<CC> p) {
        p->HH = 0;
        p->II = 0;
        int typeIdx = YY(p->EE);
        queues[typeIdx][0].push(p);
    }

    void UU(std::shared_ptr<CC> p) {
        int typeIdx = YY(p->EE);
        queues[typeIdx][p->HH].push(p);
    }

    std::shared_ptr<CC> XX() {
        for (int typeIdx = 0; typeIdx < 3; ++typeIdx) {
            for (size_t level = 0; level < queues[typeIdx].size(); ++level) {
                auto& q = queues[typeIdx][level];
                if (!q.empty()) {
                    auto p = q.front();
                    q.pop();
                    return p;
                }
            }
        }
        return nullptr;
    }

    void W() {
        for (int typeIdx = 0; typeIdx < 3; ++typeIdx) {
            for (size_t level = 2; level < queues[typeIdx].size(); ++level) {
                auto& fromQueue = queues[typeIdx][level];
                auto& toQueue = queues[typeIdx][level - 1];
                size_t size = fromQueue.size();
                for (size_t i = 0; i < size; ++i) {
                    auto p = fromQueue.front();
                    fromQueue.pop();
                    p->II++;
                    if ((size_t)p->II >= agingThreshold[level]) {
                        p->HH = level - 1;
                        p->II = 0;
                        toQueue.push(p);
                    } else {
                        fromQueue.push(p);
                    }
                }
            }
        }
    }

    int WW(int level) const {
        if (level >= 0 && level < (int)timeQuantum.size()) {
            return timeQuantum[level];
        }
        return timeQuantum.back();
    }
};

int main() {
    std::cout << "Resource-Aware TT (MLQ + MLFQ + Banker's)\n\n";

    std::vector<int> resources = {15, 8};
    NN rm(resources);
    TT ZZ(3, {2, 4, 6}, {3, 5});

    auto p1 = std::make_shared<CC>(1, AA::SYSTEM, 18, std::vector<int>{5, 2});
    auto p2 = std::make_shared<CC>(2, AA::INTERACTIVE, 8, std::vector<int>(3, 1));
    auto p3 = std::make_shared<CC>(3, AA::BATCH, 12, std::vector<int>(4, 2));

    rm.OO(p1);
    rm.OO(p2);
    rm.OO(p3);

    ZZ.OO(p1);
    ZZ.OO(p2);
    ZZ.OO(p3);

    int timeStep = 0;
    int maxTime = 60;

    while (timeStep < maxTime) {
        std::cout << "\n--- Time Step " << timeStep << " ---\n";
        ZZ.W();

        auto wokeUp = rm.RR();
        for (auto p : wokeUp) {
            std::cout << "CC " << p->DD << " unblocked\n";
            ZZ.UU(p);
        }

        auto current = ZZ.XX();
        if (!current) {
            std::cout << "No ready processes.\n";
            rm.SS();
        }
    }

    return 0;
}