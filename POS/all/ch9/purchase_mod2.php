<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body>
<?php   
    include("mysqlcntdb.php");
	//----------���X �����β��~���,�N product �� purchase ���X�_��---------	
	$SQLStr = "SELECT purchase.*, product.*  FROM purchase AS  purchase ";
	$SQLStr .= "LEFT JOIN  product AS  product ON purchase.purchprodno = product.prodno WHERE (purchtranno='$purchtranno' and purchprodno='$purchprodno')";
	$res = mysql_query($SQLStr);
	//--------- �P�_�j�M���G�O�_����------------------
	if (mysql_num_rows($res)>0)
	{
	$row = mysql_fetch_array($res);
?>
<!------ �ǵ� purchase_mod3.php �ɮ� ------>
<form name="form1" method="post" action="purchase_mod3.php?purchtranno='.$purchtranno.'&purchprodno='.$purchprodno.'">
  <table width="770" border="1" cellpadding="0" cellspacing="0" align="center" >
    <tr> 
      <td  bgcolor="#FFFFFF">  
        <table width="400" border="0" align="center">
          <tr> 
            <td width="100%" bgcolor="#9933FF" align="center"><font color="#FFFFFF">���ʸԲӸ�T</font>
            </td>                 
          </tr>
	</table>
	<table width="770">
	  <tr>
            <td align="center"> 
              <input type="submit" name="submit" value="�ק���ʸ��">
            </td>
	  </tr>
  </table>
        <table width="770" border="0" cellpadding="1" cellspacing="1" bgcolor="#99CCFF" bordercolor="#0000FF">
          <tr>           
            <td width="241" align="center"><font >���ʳ渹</font></td>
            <td width="522" align="left"><?=$row['purchtranno']?> 
		      <input  type="hidden" name="purchtranno" size="10" value="<?=$row['purchtranno']?>">
            </td>
            
          </tr>
          <tr> 
            <td width="241" align="center"><font >���~�s��</font></td>
            <td width="522" align="left"><?=$row['purchprodno']?>
			    <input type="hidden" name="purchprodno" size="10" value="<?=$row['purchprodno']?>">
            </td>
          </tr>
		  <tr> 
            <td width="241" align="center"><font >���~�W��</font></td>
            <td width="522" align="left"><?=$row['prodname']?>			   	   
            </td>
          </tr>
		  <tr>
			<td width="241" height="22" align="center">�q�ʼƶq</td>
            <td width="522" height="22"> 
                <input type="text" name="purchprodqty" size="6" value="<?=$row['purchprodqty']?>">
            </td>           
          </tr>
		   <tr> 
            <td width="241" align="center">���</td>
            <td width="522"> 
                <input type="text" name="purchpric" size="6" value="<?=$row['purchpric']?>">
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
