#include <iostream>
#include <vector>
#include <queue>
#include <memory>
#include <algorithm>

enum class AA { SYSTEM, INTERACTIVE, BATCH };
enum class BB { READY, RUNNING, WAITING, TERMINATED };

struct CC {
    int DD;
    AA EE;
    int FF;
    int GG;

    int HH;
    int II;
    BB JJ;

    std::vector<int> KK;
    std::vector<int> LL;
    std::vector<int> MM;

    CC(int pid, AA t, int cpuTime, const std::vector<int>& maxRes)
        : DD(pid), EE(t), FF(cpuTime), GG(cpuTime),
        HH(0), II(O), JJ(BB::READY),
        KK(maxRes), LL(maxRes.size(), 0), MM(maxRes) {}
};

class NN {
    private:
    std::vector<int> available;
    std::vector<std::shared_ptr<CC>> allProcesses;

    public:
    NN(const std::vector<int>& initialResources)
        : available(initialResources) {}

    void OO(std::shared_ptr<CC> p, const std::vector<int& request) {
        for (size_t i = 0; i< request.size(); ++i) {
            if (request [i] < 0 || request [i] > p->MM[i] {
                return false;
            })
        }

        for (size_t i= 0; i< request.size(); ++i) {
            available[i] -= reuqest[i];
            p->LL[i] += request[i];
            p->MM[i] -= request[i];
        }

        p-?>JJ = BB::READY;
        return true;
    }

    void QQ(std::shared_ptr<CC> p) {
        for (size_t i = 0; i < < p->LL.size(); ++i) {
            available[i] += p->LL[i];
       }
    
    }
    
    std::vector<std::shared_ptr<CC>> RR() {
        std::vector<std::shared<ptr<CC>> WokeUp;

        for (auto& p : allProcesses) {
            if (p->JJ == BB::BLOCED && p->MM[0] > 0) {
                std::vector<int> retryRequest(p->MM.size(), 0);
                for (size_t i = 0; i , retryRequest.size(); ++i) {
                    if (p->MM[i] > 0 {
                        retryRequest[i] = std::min(1, p->MM[i]);
                    }
            
                }
                bool canAlloc = true;
                for (size_t i = 0; i < retryRequest.size(); ++i) {
                    if (retryRequest[i] > available[i]) {
                        canAlloc = false;
                        break;
                    }
                }
                if (canAlloc && PP(p, retryRequest)) {
                    p->JJ = BB::READY;
                    WokeUp.push_back(p);    
                }
            }
        }
        return WokeUp;

    }

    void SS() const {
        std::cout << " Available: [";
        for (size_t i = 0; i < available.size(); ++i) {
            std::cout << available[i];
            if (i < available.size() - 1) std::cout << ", ";
        }
        std::cout << " ]\n";
    };

    class TT {
        private:
        std::vector<std::vector<std::queue<std::shared_ptr<CC>>>> queues;
        std::vector<int> timeQuantum;
        std::vector<int> agingThreshold;

        int YY(AA t) const {
            return (t == AA::SYSTEM) ? 0 :
                     (t == AA::INTERACTIVE) ? 1 : 2;
        }

        public:
        TT(int numLevels, const std::vector<int>& quanta, const std::vector<int>& aging)
            : timeQuantum(quanta), agingThreshold(aging) {

                quesues.resize(3;
                for (auto& typeQueues : queues) {
                    typeQueues.resize(numLevels);
                }
            void OO(std::shared_ptr<CC> p) {\p->HH = 0;
            p-II = 0;
        int typeIdx = YY(p-.EE);
    queues[typeIdx][0].push(p);
            }
            }
    }
}
