
--------------------------------
-- @module SGSHero
-- @extend SGSObj,SGMessageHandler
-- @parent_module cc

--------------------------------
-- @function [parent=#SGSHero] moveTo 
-- @param self
-- @param #SGSPoint sgspoint
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#SGSHero] getStatus 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#SGSHero] initAttackActions 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#SGSHero] getcategory 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#SGSHero] getStrength 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#SGSHero] doAttackAction 
-- @param self
        
--------------------------------
-- @function [parent=#SGSHero] getLuck 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#SGSHero] getRelativeDirection 
-- @param self
-- @param #cc.SGSHero sgshero
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#SGSHero] isRival 
-- @param self
-- @param #cc.SGSHero sgshero
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#SGSHero] setActionFinishedCallback 
-- @param self
-- @param #function func
        
--------------------------------
-- @function [parent=#SGSHero] getWalkAnimate 
-- @param self
-- @param #int hero_direction
-- @return Animate#Animate ret (return value: cc.Animate)
        
--------------------------------
-- @function [parent=#SGSHero] setDirection 
-- @param self
-- @param #int hero_direction
        
--------------------------------
-- @function [parent=#SGSHero] getAI 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#SGSHero] oneAIMove 
-- @param self
-- @param #function func
-- @param #cc.SGSTerrain sgsterrain
        
--------------------------------
-- @function [parent=#SGSHero] moveOneStepFinished 
-- @param self
-- @param #cc.Node node
-- @param #void void
        
--------------------------------
-- @function [parent=#SGSHero] getIntelligence 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @overload self, int         
-- @overload self, string         
-- @function [parent=#SGSHero] setStatus
-- @param self
-- @param #string str

--------------------------------
-- @function [parent=#SGSHero] init 
-- @param self
-- @param #char char
-- @param #int hero_side
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#SGSHero] setActive 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#SGSHero] setTerrain 
-- @param self
-- @param #cc.SGSTerrain sgsterrain
        
--------------------------------
-- @function [parent=#SGSHero] attackActionFinished 
-- @param self
-- @param #cc.Node node
-- @param #void void
        
--------------------------------
-- @function [parent=#SGSHero] initDataNum 
-- @param self
        
--------------------------------
-- @function [parent=#SGSHero] attacked 
-- @param self
        
--------------------------------
-- @function [parent=#SGSHero] initActions 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#SGSHero] getSide 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#SGSHero] update 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#SGSHero] attackHero 
-- @param self
-- @param #cc.SGSHero sgshero
        
--------------------------------
-- @overload self, string         
-- @overload self, int         
-- @function [parent=#SGSHero] setAI
-- @param self
-- @param #int hero_ai

--------------------------------
-- @function [parent=#SGSHero] initCategory 
-- @param self
        
--------------------------------
-- @function [parent=#SGSHero] initSpecActions 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @overload self, int         
-- @overload self, char         
-- @function [parent=#SGSHero] faceTo
-- @param self
-- @param #char char

--------------------------------
-- @function [parent=#SGSHero] isActive 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#SGSHero] getStamina 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#SGSHero] getAgility 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#SGSHero] getAttackAnimate 
-- @param self
-- @return Animate#Animate ret (return value: cc.Animate)
        
--------------------------------
-- @function [parent=#SGSHero] getCommand 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#SGSHero] doAction 
-- @param self
-- @param #char char
        
--------------------------------
-- @function [parent=#SGSHero] moveOneStep 
-- @param self
-- @param #array_table array
        
--------------------------------
-- @function [parent=#SGSHero] counterAttackFinished 
-- @param self
-- @param #cc.Node node
-- @param #void void
        
--------------------------------
-- @function [parent=#SGSHero] create 
-- @param self
-- @param #char char
-- @param #int hero_side
-- @param #SGObserver sgobserver
-- @return SGSHero#SGSHero ret (return value: cc.SGSHero)
        
--------------------------------
-- @function [parent=#SGSHero] SGSHero 
-- @param self
-- @param #SGObserver sgobserver
        
return nil
