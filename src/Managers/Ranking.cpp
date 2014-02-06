#include "Ranking.h"

//------------------------------
Ranking::Ranking(void){

    

}

//------------------------------
void Ranking::saveXmlScore(Score score){
    rank.push_back(score);
    
    addTag("ranking");
    pushTag("ranking");
    
    for(int i = 0; i < rank.size(); i++){
        
        addTag("score");
        pushTag("score",i);
        
        addValue("idPlayer", rank[i].idPlayer);
        addValue("lastMission", rank[i].lastMission);
        addValue("points", rank[i].points);
        popTag();//pop position
    }
    popTag(); //pop position
    saveFile("ranking.xml");
}

//-----------------------------
void Ranking::loadXmlRanking(){
    
    
    if(loadFile("ranking.xml")){
        pushTag("ranking");
        numberOfSavedPoints = getNumTags("score");
        for(int i = 0; i < numberOfSavedPoints; i++){
            pushTag("score", i);
            
            Score s;
            s.idPlayer = getValue("idPlayer", 0);
            s.lastMission = getValue("lastMission", 0);
            s.points = getValue("points", 0);
            
            rank.push_back(s);
            popTag();
        }
        
        popTag(); //pop position
    }
    else{
        ofLogError("Position file did not load!");
    }

}

//-----------------------------
Score Ranking::getMaxScore(void){
    Score maxScore;
    maxScore.points = 0;
    for(int i = 0; i < rank.size(); i++){
        if (maxScore.points < rank[i].points)
            maxScore = rank[i];
    }
    
    return maxScore;
}