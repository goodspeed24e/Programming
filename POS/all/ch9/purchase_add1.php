<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body>
<?php	
	include("mysqlcntdb.php");
	//-------------- �N�p�ƾ���ƪ������ʭp�ƭȨ��X--------------
	$cntid="purc";
	include("counter.php");
	$dt=date("Y-m-d");

?>
<script language="JavaScript">
//-------------- �ˬd���~�ƶq--------------
function checkprodqty(fld){
   if (fld.value == ""){
      alert("�п�J���~�ƶq!");
      fld.focus();
      fld.select();
   }
}
</script>	
<form name="form1" method="post" action="purchase/purchase_add2.php">
  <table width="780" border="1" cellpadding="0" cellspacing="0" align="center" bordercolor="#0000FF">
    <tr>
	  <td   bgcolor="#FFFFFF">  
	<table  border="1" align="center" bgcolor="#99CCFF" cellpadding="0" cellspacing="0" width="780">
          <tr  bgcolor="#99CCFF"> 
            <td  bgcolor="#9933FF" align="center"> 
             <font color="#FFFFFF">�s�W���ʳ���</font>
            </td> 
			  <td align="center"> 
              <input type="submit" name="submit" value="�s�W���ʳ���">
            </td>                 
          </tr>
        </table>	
      <table width="780" border="1" cellpadding="0" cellspacing="0" bgcolor="#99CCFF"  align="center">        
	      <tr> 
            <td width="103" align="center">���ʳ渹</td>
            <td width="187"><input type="text" name="purcmtranno" size="10" value="<?=$purccnt;?>">                
            </td>
            <td width="96" align="center">��f���</td>
            <td width="351"> 
                <input type="text" name="purcmdate" size="12" value="<?=date("Y-m-d")?>">
            </td>
          </tr>        
          <tr>            
            <td width="96" height="22" align="center">�t�ӽs��</td>
           <!-- </td>-->
            <td width="187" height="22">
<?php
    //-------------- �N�t�Ӹ�ƪ�����ƥ������X--------------
	$SQLStr = "SELECT * FROM vend";
	$res = mysql_query($SQLStr);
	if ($res)
	{
	  $num = mysql_num_rows($res);
    //---------- �N�t�ӽs��/�W�٪����ȧe�{������W--------------   
          echo "<select name='purcmvend'>";
	  for ($i=0;$i<$num;$i++)
	  {
	    $row = mysql_fetch_array($res);
	    echo "<option value='" . $row['vendno'] . "'>" .$row['vendno'] ." / ". $row['vendname'] . "</option>";
	  }
            echo "</select>";	
	}		
	else
	// ��ƪ��L�t�Ӹ�� 
		echo "�ثe�L�t�Ӹ��";
?>           
            </td>
			 <td width="96" align="center">�������O</td>
            <td width="351"> 
                <input type="text" name="purcmtype" size="10">
            </td>
          </tr>        
        </table>       
		<table width="780"  border="1"   bgcolor="#99CCFF" cellpadding="0" cellspacing="0" align="center">        
          <tr>
            <td  align="center">���~�s��/���~�W��/���</td>
            <td  align="center">���ʼƶq</td>
            <td  align="center"></td>           
          </tr>
  <?php		  
        //-------------- �N���~�s��/�W��/��������ȧe�{������W--------------		
		  for ($i=0;$i<8;$i++)
		 {         
		    echo "<tr>";
            echo "<td align='center'>";
              //---------- �N���~�s��/�W�٪����ȧe�{������W--------------	
			  $SQLStr = "SELECT * FROM product";
	          $res = mysql_query($SQLStr);
	          if ($res)
	          {
	            $num = mysql_num_rows($res); 
                echo "<select name='purchprodno[]'>";
	            for ($k=0;$k<$num;$k++)
	            {
	              $row = mysql_fetch_array($res);
	              echo "<option value='" . $row['prodno'] . "'>" . $row['prodno'] ."/". $row['prodname'] . "/".$row['prodipric']."</option>";
				  $purchpric[$k]=$row['prodipric'];
	            }
                  echo "</select>";			
	          }		
	          else 
              //---------- �L���~���--------------------			  
		          echo "�ثe�L���~���";				 
			 echo "</td>"; 
            echo "<td align='center'><input name='purchprodqty[]' type='text' size='6' maxlength='6' onblur='checkprodqty(this)'></td>";
           echo "</tr>";
		  }  
		  ?>	  
        </table>     
      </td>
    </tr>
  </table>
</form>
</body>
</html>