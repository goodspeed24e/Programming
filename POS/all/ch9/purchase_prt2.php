<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body  onLoad="window.print()">
<?php 
    // -------------�q���ʥD��ƪ�,���X�ŦX���ʳ渹�����---------------
	include("mysqlcntdb.php");	
	$SQLStr = "SELECT * FROM purchmst  WHERE ( purcmtranno = '$purchtranno')";	
	
	$res = mysql_query($SQLStr);	
    //--------------�p���`���Ƥέ���------------------
    if (mysql_num_rows($res)>0)	
	{
	$row=mysql_fetch_row($res);		
?>
<!------ �����C�L,�ǵ��D�ؿ�------>
<form name="form1" method="post" action="../index.php?Select=10">
  <table width="604" border="0" align="center" cellspacing="0" cellpadding="0" >
    <tr > 
      <td    align="left"><font size="-1"> 
<?php
     //--------------���ƿ�ܧe�{�γs��---------------
     echo "���ʳ�<br>";	
	 echo "���ʳ渹:".$purchtranno."&nbsp;&nbsp;�����t��:".$purcmvend."/". $purcmvendname  ."&nbsp;&nbsp;��f���:".$purcmdate."&nbsp;&nbsp;�������O:".$purcmtype."<br> ";	
	
?>
    </font></td>
    </tr>
  </table>
  <table width="601" border="0" align="center" cellpadding="0" cellspacing="0" >
    <tr> 
      <td width="601"> 
        <table width="595" border="0" align="center" >
		    <tr> 
            <td  align="left" colspan="4"> 
              <hr  size="1" color="#000000"  width="100%">
            </td>
          </tr>
          <tr>                     
            <td width="111"  align="left"><font size="-1">  
             ���~�s��</font>
            </td>
            <td width="210"  align="left"><font size="-1">  
              ���~�W��</font>
            </td>
            <td width="161"  align="left"><font size="-1">  
              ���ʼƶq</font>
            </td>
            <td width="95" align="left"><font size="-1">  
              ���</font>
            </td>             
          </tr>	
		    <tr> 
            <td  align="left" colspan="4"> 
              <hr  size="1" color="#000000"  width="100%">
            </td>
          </tr>	  
	<?php
      //--------------��ܭ��ƾP�f���Ƨe�{�γs�������\��-----------	 
	  $SQLStr="select * from purchase where  purchtranno =  '$purchtranno' ";
	  $res = mysql_query($SQLStr);	

       while (list($purchtranno, $purchprodno, $purchprodqty, $purchinqty, $purchpric, $purchunit, $purchprodname)=mysql_fetch_row($res))
		{
       //---------------���ʥD��ƪ�,���X�ŦX���ʳ�,�����ƪ���ƨçe�{-------
            echo "<tr border='0'   >";	
			echo "<td align='left'><font size='-1'>" . $purchprodno  . "</font></td>\n";
			echo "<td align='left'><font size='-1'>" . $purchprodname . "</font></td>\n";
			echo "<td align='left'><font size='-1'>" . $purchprodqty . "</font></td>\n";	
			echo "<td align='left'><font size='-1'>" . $purchpric . "</font></td>\n";	
			echo "</tr>";		  	
		}	
?>      
        </table>
      </td>
    </tr>
  </table>    
</form>
<?
}
else
	{	
	 $msg="�L�����ʳ�";
	 include("windowsclose.php");
	}
?>
</body>
</html>
	
