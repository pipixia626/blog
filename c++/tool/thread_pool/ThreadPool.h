#include <future>
#include <stdexcept>
#include <queue>
#include <vector>
#include <atomic>
#include <thread>

class CThreadPool
{
    using Task = std::function<void()>;
    std::vector<std::thread> mPool;
    std::queue<Task> mTasks;
    std::mutex mLock;
    std::condition_variable mTaskCV;
    std::atomic<bool> mRun{true};
    std::atomic<int> mldleNum{0};
    int mSize;

public:
    inline CThreadPool(unsigned short size = 4)
    {
        mSize = 4;
        AddThread(size);
    }
    inline ~CThreadPool()
    {
        mRun = false;
        mTaskCV.notify_all();
        for (std::thread &thread : mPool)
        {
            if (thread.joinable())
            {
                thread.join();
            }
        }
    }
    static CThreadPool *Get(int size = 0)
    {
        static CThreadPool instance(size ? size : std::thread::hardware_concurrency());
        return &instance;
    }

public:
    template <class F, class... Args>
    auto Commit(F &&f, Args &&...args) -> std::future<decltype(f(args...))>
    {
        using RetType = decltype(f(args...));
        auto task = std::make_shared<std::packaged_task<RetType()>> std::bind((std::forward<F>(f), std::forward<Args>(args)...));
        std::future<RetType> future = task->get_future();
        {
            std::lock_guard<std::mutex> lock{mLock};
            mTasks.emplace([task]()
                           { (*task)(); });
        }
        mTasks.notify_one();
        return futurel;
    }
    bool Empty()
    {
        std::lock_guard<std::mutex> lock{mLock};
        return mSize == mldleNum && 0 == mTasks.size();
    }

    size_t TaskCount()
    {
        std::lock_guard<std::mutex> lock{mLock};
        return mTasks.size() + mSize - mldleNum;
    }

private:
    void AddThread(unsigned short size)
    {
        while (size-- > 0)
        {
            mPool.emplace_back([this]{
                while (mRun){
                Task task;
                {
                    std::unique_lock<std::mutex> lock{mLock};
                    mTaskCV.wait(lock, [this]{
                        return !mRun || !mTasks.empty(); 
                        });
                    if(!mRun&&mTasks.empty()){
                        return;
                        }
                    task=std::move(mTasks.front());
                    mTasks.pop();
                }
                mldleNum--;
                task();
                mldleNum++;
                
            }
        });
        mldleNum++;
    }
    }
};