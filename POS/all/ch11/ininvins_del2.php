<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body>
<?php   
    include("mysqlcntdb.php");
	//----------���X�ŦX���󪺩Ҧ��i�f�����---------	
	$SQLStr = "SELECT * FROM transaction  WHERE (tranno='$tranno' and tranpono='$tranpono' and tranprodno='$tranprodno')";
	$res = mysql_query($SQLStr);
		
	//------------------------ �P�_�j�M���G�O�_����--------------------------------
	if (mysql_num_rows($res)>0)	
	{
	$row = mysql_fetch_array($res);
?>
<!------ ����R���@�~,�ǵ�ininvins_del3.php �ɮ�,�s����Ʈw ------>
<form name="form1" method="post" action="ininvins_del3.php">
  <table width="770" border="1" cellpadding="0" cellspacing="0" align="center" >
    <tr> 
      <td  bgcolor="#FFFFFF">  
        <table width="400" border="0" align="center">
          <tr> 
            <td width="100%" bgcolor="#9933FF" align="center"><font color="#FFFFFF">�i�f�ԲӸ�T</font>
            </td>                      
          </tr>
	</table>
	<table width="770">
	  <tr>
            <td align="center"> 
              <input type="submit" name="submit" value="�R���i�f���">
            </td>
	  </tr>
  </table>
<!--�e�{�i�f���,�ѧP�_---------->  
        <table width="770" border="0" cellpadding="1" cellspacing="1" bgcolor="#99CCFF" >
          <tr>           
            <td width="241" align="center"><font >�i�f�渹</font></td>
            <td width="522" align="left"><?=$row['tranno']?>	
			 <input  type="hidden" name="tranno" size="10" value="<?=$row['tranno']?>">     
            </td>            
          </tr>
          <tr> 
            <td width="241" align="center"><font >���~�s��</font></td>
            <td width="522" align="left"><?=$row['tranprodno']?>
			 <input type="hidden" name="tranprodno" size="10" value="<?=$row['tranprodno']?>">   
            </td>
          </tr>
		  <tr> 
            <td width="241" align="center"><font >���~�W��</font></td>
            <td width="522" align="left"><?=$row['prodname']?>			    		   
            </td>
          </tr>
          <tr>
            <td width="241" align="center"><font >���ʳ渹</font> </td>
            <td width="522" align="left"><?=$row['tranpono']?> 
			  <input type="hidden" name="tranpono" size="10" value="<?=$row['tranpono']?>">              
            </td>            
          </tr>
          <tr>
            <td width="241" height="22" align="center"><font >�i�f���</font> </td>
            <td width="522" height="22" align="left"><?=$row['trandate']?>                
            </td>            
          </tr>
          <tr>            
            <td width="241" height="22" align="center">�t�ӽs��</td>
            <td width="522" height="22" align="left"><?=$row['tranvendno']?>
			<input type="hidden" name="tranvendno" size="10" value="<?=$row['tranvendno']?>">                  
            </td>			           
          </tr>
		  <tr>
			<td width="241" height="22" align="center">���~�ƶq</td>
            <td width="522" height="22"><?=$row['tranprodqty']?>			               
            </td>           
          </tr>
		  <tr>
			<td width="241" height="22" align="center">���~���</td>
            <td width="522" height="22"><?=$row['tranunit']?>              
            </td>           
          </tr>
		  <tr> 
            <td width="241" align="center">���</td>
            <td width="522"><?=$row['tranpric']?>			            
            </td>
		  </tr>		   
		</td>
    </tr> 
  </table>
</form>
<?
}
else
	{
	 $msg="�L���i�f��";
	 include("windowsclose.php");
	}
?>
</body>
</html>

