class BaseAIEntity
{
private:
    int mID;

    void SetID(int id)
    {
        mID = id;
    }
public:
    BaseAIEntity(int id)
    {
        SetID(id);
    }
    
    int ID()const{return mID;}
};