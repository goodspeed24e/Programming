<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body>
<?php	
	include("mysqlcntdb.php");	
    //-------------- �N���ʥD��ƪ�����ƲŦX���ʽs������ƨ��X--------------
	$SQLStr = "SELECT purchmst.* FROM purchmst  WHERE purcmtranno='$purcmtranno'";	
	$res = mysql_query($SQLStr);

 while (list($purcmtranno, $purcmvend, $purcmdate, $purcmtype)=mysql_fetch_row($res))
 {
 ?>
 <!------ �ǵ� purchmst_del3.php �ɮ� ------>
<form name="form1" method="post" action="purchmst_del3.php?purcmtranno='.$purcmtranno.'">
  <table width="780" border="1" cellpadding="0" cellspacing="0" align="center">
    <tr> 
	<table  border="1" align="center" bgcolor="#99CCFF" cellpadding="0" cellspacing="0" width="780">
          <tr  bgcolor="#99CCFF"> 
            <td  bgcolor="#9933FF" align="center"> 
             <font color="#FFFFFF">�R�����ʥD��ƪ����</font>
            </td> 
			  <td align="center"> 
              <input type="submit" name="submit" value="�R�����ʥD��ƪ����">
            </td>                 
          </tr>
        </table>	
      <table width="780" border="1" cellpadding="0" cellspacing="0" bgcolor="#99CCFF"  align="center">        
	      <tr> 
            <td width="103" align="center">���ʳ渹</td>
            <td width="187"><?=$purcmtranno; ?>
			 <input  type="hidden" name="purcmtranno" size="10" value="<?=$purcmtranno;?>">                
            </td>
		 </tr>	
		 <tr>
            <td width="96" align="center">�����t��</td>
            <td width="351"><?=$purcmvend; ?>               
            </td>
          </tr>        
          <tr>            
            <td width="96" height="22" align="center">��f���</td>
			 <td width="351"><?=$purcmdate; ?>               
            </td>
			
		  </tr>        
          <tr> 
			 <td width="96" align="center">�������O</td>
            <td width="351"><?=$purcmtype; ?>              
            </td>
          </tr> 
		</table>  
      </td>
    </tr>
  </table>
</form>
<?php
}
?>
</body>
</html>
 