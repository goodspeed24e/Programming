<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body>
<?php	
	include("mysqlcntdb.php");
	$cntid="tran";	
	include("counter.php");
	$dt=date("Y-m-d");
//-------------- �N�t�Ӹ�ƪ�����ƥ������X--------------
	$SQLStr = "SELECT * FROM vend";
	$res = mysql_query($SQLStr);

?>
<!---------------- �������ˬd-------------->
<script language="JavaScript">
//-------------- �ˬd�ƶq--------------
function checkprodqty(objEle){
   if (objEle.value == ""){
      alert("�п�J���~�ƶq!");
      objEle.focus();
      objEle.select();
   }
}
</script>	
<!------�i�Jininvpur_add3.php ,�N�i�f��ƿ�J��Ʈw��---------->
<form name="form1" method="post" action="ininv/ininvpur_add3.php">
  <table width="780" border="1" cellpadding="0" cellspacing="0" align="center" >
    <tr> 
	<table  border="1" align="center" bgcolor="#99CCFF" cellpadding="0" cellspacing="0" width="780">
          <tr  bgcolor="#99CCFF"> 
            <td  bgcolor="#9933FF" align="center"> 
             <font color="#FFFFFF">�̱��ʳ��J�i�f���</font>
            </td> 
			  <td align="center"> 
              <input type="submit" name="submit" value="�s�W�i�f���">
            </td>                 
          </tr>
        </table>	
      <table width="780" border="1" cellpadding="0" cellspacing="0" bgcolor="#99CCFF"  align="center">        
	      <tr> 
            <td width="103" align="center">�i�f�渹</td>
            <td width="187"><input type="text" name="tranno" size="10" value="<?=$trancnt;?>">                
            </td>
            <td width="96" align="center">�i�f���</td>
            <td width="351"> 
                <input type="text" name="trandate" size="12" value="<?=date("Y-m-d")?>">
            </td>
          </tr>
        
          <tr>            
            <td width="96" height="22" align="center">�t�ӽs��</td>
           <!-- </td>-->           
            <td width="187">
<?php
//-------------------- �N�t�Ӹ�ƪ�����ƥ������X----------------------------
	$SQLStr = "SELECT * FROM vend";
	$res = mysql_query($SQLStr);
	if ($res)
	{
	  $num = mysql_num_rows($res);
//------------------- �e�{�t�ӦW�٪�����,�ѿ��------------------------------------
           echo "<select name='tranvendno'>";
	  for ($i=0;$i<$num;$i++)
	  {
	    $row = mysql_fetch_array($res);
	    echo "<option value='" . $row['vendno'] . "'>" . $row['vendname'] . "</option>";
	  }
            echo "</select>";	
	}		
	else 
		echo "�ثe�t�ӵL�W��";
?>
            </td>
			<td width="96" align="center">���ʳ渹</td>
            <td width="351"><?=$tranpono;?> 
                <input type="hidden" name="tranpono" size="12" value="<?=$tranpono;?>">
            </td>
          </tr>        
        </table>       
		<table width="780"  border="1"   bgcolor="#99CCFF" cellpadding="0" cellspacing="0" align="center">        
          <tr>
            <td  align="center" width="542">���~�s��/���~�W��/���ʼƶq/���</td>          
            <td width="238" align="center">�i�f�ƶq</td>  
          </tr>
  <?php		  
    //-------------- ��J�i�f���~�������--------------
	  for ($i=0;$i<8;$i++)
		 { 
          echo "<tr>";          
            echo "<td align='center'>";
    //-------------- �N���ʸ�ƪ��ŦX���󪺸�ƥ������X--------------	
    $SQLStr = "SELECT product.*, purchase.* FROM purchase AS purchase ";
	$SQLStr .= "LEFT JOIN product AS product ON purchase.purchprodno =  product.prodno WHERE purchtranno='$tranpono'";	
	$res = mysql_query($SQLStr);
	if ($res)
	{
	  $num = mysql_num_rows($res); 
          echo "<select name='tranprodno[]'>";
	  for ($j=0;$j<$num;$j++)
	  {
	    $row = mysql_fetch_array($res);		
	    echo "<option value='" . $row['purchprodno'] . "'>" . $row['purchprodno'] ."&nbsp;&nbsp;&nbsp;/&nbsp;&nbsp;&nbsp;" . $row['prodname'] ."&nbsp;&nbsp;&nbsp;/&nbsp;&nbsp;&nbsp;".$row['purchprodqty']. "&nbsp;&nbsp;&nbsp;/&nbsp;&nbsp;&nbsp;".$row['purchpric']. "</option>";
	  }
            echo "</select>";
    //-------------- �N���ʤβ��~�����ȧe�{������W--------------
     echo "</td>";			      
     echo "<td align='center'><input name='tranprodqty[]' type='text' size='6' maxlength='6' onblur='checkprodqty(this)'></td>";

	}
	//-------------- ���ʸ�ƪ��L�ŦX���--------------
	else 
 	 echo "�ثe�L���ʸ��";
	 echo "</td>";			      
     echo "<td align='center'>&nbsp;</td>";
    }	
		  ?>	  
        </table>     
      </td>
    </tr>
  </table>
</form>
</body>
</html>
